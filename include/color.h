#pragma once

namespace twenty {

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

template <typename value_t = double> constexpr value_t sqr(const value_t x) {
  return x * x;
}

constexpr char mono(point<color_t> const& rgb) {
  return rgb.x * 0.15 + rgb.y * 0.7 + rgb.z * 0.15;
}

constexpr int offset(pixel<int> const& p, const int width, const int depth) {
  return p.i * depth + p.j * width * depth;
}

inline void write_pixel(screenbuffer_t& buffer, pixel<int> const& p,
                        const int width, point<color_t> const& rgb) {
  const auto offc = offset(p, width, depth);
  buffer[offc] = rgb.x;
  buffer[offc + 1] = rgb.y;
  buffer[offc + 2] = rgb.z;
}

point<color_t> meancolor(std::vector<point<color_t>> const& light_source) {
  unsigned r = 0;
  unsigned g = 0;
  unsigned b = 0;
  unsigned n = 0;
  for (auto const& src : light_source) {
    r += src.x;
    g += src.y;
    b += src.z;
    n++;
  }
  return point<color_t>{color_t(r / n), color_t(g / n), color_t(b / n)};
}

void ambient(screenbuffer_t& buffer, point<color_t> const& light,
             rect<int> const& screen) {

  for (int i = 0; i < screen.width; ++i) {
    for (int j = 0; j < screen.height; ++j) {
      const auto faderatio = double(screen.height - j) / screen.height;
      const auto ambrgb = point<color_t>{color_t(light.x * faderatio),
                                         color_t(light.y * faderatio),
                                         color_t(light.z * faderatio)};
      const auto point = pixel<int>{i, j};
      write_pixel(buffer, point, screen.width, ambrgb);
    }
  }
}

} // namespace twenty
