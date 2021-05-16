#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

#include "image.h"

using namespace std::literals::chrono_literals;

namespace {

using color_t = unsigned char;
using screenbuffer_t = std::vector<color_t>;

constexpr auto depth = 3;

template <typename value_t> struct rect {
  value_t width;
  value_t height;
};

template <typename value_t> struct pixel {
  value_t i;
  value_t j;
};

template <typename value_t> struct point {
  value_t x;
  value_t y;
  value_t z;
};

constexpr int offset(pixel<int> const& p, const int width, const int depth) {
  return p.i * depth + p.j * width * depth;
}

constexpr char mono(point<color_t> const& rgb) {
  return rgb.x * 0.15 + rgb.y * 0.7 + rgb.z * 0.15;
}

inline void write_pixel(screenbuffer_t& buffer, pixel<int> const& p,
                 const int width, point<color_t> const& rgb) {
  const auto offc = offset(p, width, depth);
  buffer[offc] = rgb.x;
  buffer[offc + 1] = rgb.y;
  buffer[offc + 2] = rgb.z;
}

constexpr inline double sqr(const double x) { return x * x; }

void shade_sphere(screenbuffer_t& buffer, rect<int> const& screen,
                  const double kd, const double ks, const int spec_index,
                  pixel<int> const& center, const int radius, point<color_t> const& light_source) {
  constexpr auto Ilight = 140;
  constexpr auto K = 70.0;
  constexpr auto IaKa = 0.2;
  constexpr auto Hx = 0.325058, Hy = 0.325058, Hz = 0.888074;
  constexpr auto dx = 110.0, dy = 110.0, dz = 110.0;
  constexpr auto Lx = 0.57735, Ly = 0.57735, Lz = 0.57735;
  constexpr auto epsilon = 1e-8;

  const auto rsquare = sqr(radius);
  for (auto y = -radius; y < radius; ++y) {
    const auto ysquare = sqr(y);
    for (auto x = -radius; x < radius; ++x) {
      const auto xsquare = sqr(x);
      if ((xsquare + ysquare) <= rsquare) {
        const auto z = std::round(std::sqrt(rsquare - xsquare - ysquare));
        const auto zsquare = sqr(z);
        const auto denom = std::sqrt(xsquare + ysquare + zsquare);
        point<double> xn;
        xn.x = x / denom;
        xn.y = y / denom;
        xn.z = z / denom;
        // calculate LN and NnH
        auto dist = 0.0, nh = 0.0, nnh = 0.0;
        auto ldotn = xn.x * Lx + xn.y * Ly + xn.z * Lz;
        if (ldotn <= epsilon) {
          ldotn = 0.0;
        } else {
          dist = std::sqrt(sqr(dx - x) + sqr(dy - y) + sqr(dz - z));
          nh = Hx * xn.x + Hy * xn.y + Hz * xn.z;
          nnh = std::exp(spec_index * std::log(nh));
        }
        // end calculate LN and NnH
        const auto ambientterm = IaKa;
        color_t ig, ir, ib;
        if (ldotn <= epsilon) {
          ig = std::round(255.0 * ambientterm);
          ir = ib = 0;
        } else {
          const auto distfactor = Ilight / (dist + K);
          const auto diffuseterm = distfactor * kd * ldotn;
          const auto specularterm = distfactor * ks * nnh;
          ir = std::round(light_source.x * specularterm);
          ig = std::round(light_source.y * (ambientterm + diffuseterm + specularterm));
          ib = std::round(light_source.z * specularterm);
        }

        pixel<int> p{center.i + x, center.j + y};
        point<color_t> rgb{ir, ig, ib};

        write_pixel(buffer, p, screen.width, rgb);
      }
    }
  }
}

point<color_t> meancolor(std::vector<point<color_t>> const& light_source) {
  unsigned r = 0;
  unsigned g = 0;
  unsigned b = 0;
  unsigned n = 0;
  for(auto const& src: light_source) {
    r += src.x;
    g += src.y;
    b += src.z;
    n++;
  }
  return point<color_t>{color_t(r/n), color_t(g/n), color_t(b/n)};
}

void ambient(screenbuffer_t& buffer, point<color_t> const& light, rect<int> const& screen) {

  for(int i=0; i<screen.width; ++i) {
    for(int j=0; j<screen.height; ++j) {
      const auto faderatio = double(screen.height-j)/screen.height;
      const auto ambrgb = point<color_t>{color_t(light.x*faderatio), color_t(light.y*faderatio), color_t(light.z*faderatio)};
      const auto point = pixel<int>{i, j};
      write_pixel(buffer, point, screen.width, ambrgb);
    }
  }


}

} // namespace

int main(int argc, char* argv[]) {

  if (argc < 2) {
    std::cerr << "filename expected." << std::endl;
    return 1;
  } else {

    const auto filename = argv[1];

    constexpr int height = 4000;
    constexpr int width = 4000;
    constexpr int depth = 3;
    constexpr auto buffer_size = height * width * depth;

    rect<int> screen{width, height};

    const auto light_source = point<color_t>{78, 255, 178};
  
    screenbuffer_t buffer;
    buffer.resize(buffer_size);
    ambient(buffer, light_source, screen);

    constexpr auto kd = 0.25;
    constexpr auto ks = 0.95;
    constexpr auto spec_idx = 1.0;

    constexpr auto N = 20;
    constexpr double spec_step = (ks-kd)/N;

    double kz = 0.0;

    constexpr auto Nx = 5;
    for(int i=0; i<Nx; ++i) {
      const auto xstep = width/Nx;
      const auto Ny = N/Nx;
      for(int j=0; j<Ny; ++j) {
        const auto ystep = height/Ny;
        constexpr auto radius = std::min(width, height)/(std::max(Nx, Ny)+2)/2;
        pixel<int> center{i*xstep + xstep/2, j*ystep + ystep/2};
        shade_sphere(buffer, screen, kd + kz, ks - kz, spec_idx, center, radius, light_source);
        kz += spec_step;
      }
    }



    auto jpeg = image::jpegfile(filename);

    jpeg.write(buffer, width, height);
    std::cout << filename << std::endl;
  }


  std::this_thread::sleep_for(60s);

  return 0;
}
