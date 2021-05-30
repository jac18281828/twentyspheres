#pragma once

#include <array>

#include "color.h"
#include "tripple.h"
#include "twenty.h"

namespace twenty {

template <int d = 3> class bitmap {
public:
  using buffer_t = std::vector<color_t>;

  bitmap() = default;

  bitmap(const int width, const int height) : m_width(width), m_height(height) {
    m_buffer.reserve(width * height * depth());
  }

  bitmap& operator=(bitmap const& b) = default;
  bitmap& operator=(bitmap&& b) = default;

  void set_pixel(int x, int y, color3 const& rgb) {
    const auto offc = x * depth() + y * m_width * depth();
    m_buffer[offc] = rgb[0];
    m_buffer[offc + 1] = rgb[1];
    m_buffer[offc + 2] = rgb[2];
  }

  void set_pixel(pixel<int> const& p, color3 const& rgb) { set_pixel(p.x, p.y, rgb); }

  void fill(color3 const& rgb) {
    for (int x = 0; x < width(); ++x) {
      for (int y = 0; y < width(); ++y) {
        set_pixel(x, y, rgb);
      }
    }
  }

  buffer_t const& buffer() const { return m_buffer; }

  int width() const { return m_width; }

  int height() const { return m_height; }

  constexpr int depth() const { return d; }

private:
  int m_width;
  int m_height;
  buffer_t m_buffer;
};

} // namespace twenty
