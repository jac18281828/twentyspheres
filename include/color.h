#pragma once

#include "tripple.h"
#include "twenty.h"

namespace twenty {

constexpr auto depth = 3;

template <typename value_t> struct rect {
  value_t width;
  value_t height;
};

template <typename value_t> struct pixel {
  value_t x;
  value_t y;
};

constexpr color_t mono(color3 const& rgb) { return rgb[0] * 0.15 + rgb[1] * 0.7 + rgb[2] * 0.15; }

constexpr int offset(pixel<int> const& p, const int width, const int depth) {
  return p.x * depth + p.y * width * depth;
}

} // namespace twenty
