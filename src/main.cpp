#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

#include "image.h"

using namespace std::literals::chrono_literals;

namespace {

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

constexpr char mono(point<char> const& rgb) {
  return rgb.x * 0.15 + rgb.y * 0.7 + rgb.z * 0.15;
}

inline void write_pixel(std::vector<char>& buffer, pixel<int> const& p,
                 const int width, point<char> const& rgb) {
  const auto offc = offset(p, width, depth);
  const auto c = mono(rgb);
  buffer[offc] = c;
  buffer[offc + 1] = c*1.05;
  buffer[offc + 2] = c;
}

constexpr inline double sqr(const double x) { return x * x; }

void shade_sphere(std::vector<char>& buffer, rect<int> const& screen,
                  const double kd, const double ks, const int spec_index,
                  pixel<int> const& center, const int radius) {
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
        char ig, irb;
        if (ldotn <= epsilon) {
          ig = std::round(255.0 * ambientterm);
          irb = 0;
        } else {
          const auto distfactor = Ilight / (dist + K);
          const auto diffuseterm = distfactor * kd * ldotn;
          const auto specularterm = distfactor * ks * nnh;
          ig = std::round(255.0 * (ambientterm + diffuseterm + specularterm));
          irb = std::round(255.0 * specularterm);
        }

        pixel<int> p{center.i + x, center.j + y};
        point<char> rgb{irb, ig, irb};

        write_pixel(buffer, p, screen.width, rgb);
      }
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
    constexpr auto color = 255;
    constexpr auto buffer_size = height * width * depth;
  
    std::vector<char> buffer;
    buffer.resize(buffer_size);
    std::fill(std::begin(buffer), std::end(buffer), color);

    rect<int> screen{width, height};

    constexpr auto kd = .00;
    constexpr auto ks = 1.0;
    constexpr auto spec_idx = 1.0;

    constexpr auto N = 20;
    constexpr auto radius = width/(N+1);

    constexpr double spec_step = 1.0/N;

    double kz = 0.0;

    for(int i=0; i<5; ++i) {
      const auto xstep = width/5;
      for(int j=0; j<4; ++j) {
        const auto ystep = height/4;
        pixel<int> center{i*xstep + xstep/2, j*ystep + ystep/2};
        shade_sphere(buffer, screen, kd + kz, ks - kz, spec_idx, center, radius);
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
