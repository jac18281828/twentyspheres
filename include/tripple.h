#pragma once

#include <array>
#include <cmath>

#include "twenty.h"

namespace twenty {

template <typename value_type, int n = 3> class tripple {
  static constexpr bool is_approx_equal(const value_type x, const value_type y) {
    return std::fabs(x - y) <= ((std::fabs(x) < std::fabs(y)) ? std::fabs(y) : std::fabs(x)) * epsilon;
  }

public:
  static constexpr int size = n;

  constexpr tripple(value_type const x, value_type const y, value_type const z) : m_value{{x, y, z}} {
    static_assert(size == 3);
  }

  constexpr tripple(value_type const x, value_type const y, value_type const z, value_type const w)
      : m_value{{x, y, z, w}} {
    static_assert(size == 4);
  }

  constexpr tripple(std::array<value_type, n> const& value) : m_value(value) {}

  constexpr explicit tripple(const value_type v) { m_value.fill(v); }

  constexpr tripple() : tripple(0) {}

  constexpr tripple(tripple const& t) = default;

  constexpr tripple(tripple&& t) = default;

  tripple& operator=(tripple const& t) = default;

  tripple& operator=(tripple&& t) = default;

  bool operator==(tripple const& t) const {
    for (int i = 0; i < size; i++) {
      if (!is_approx_equal(m_value[i], t.m_value[i]))
        return false;
    }
    return true;
  }

  tripple operator+(tripple const& t) const {
    static_assert(size == t.size);
    auto value = tripple(*this);
    for (int i = 0; i < size; ++i) {
      value.m_value[i] += t.m_value[i];
    }
    return value;
  }

  tripple operator-(tripple const& t) const {
    static_assert(size == t.size);
    auto value = tripple(*this);
    for (int i = 0; i < size; ++i) {
      value.m_value[i] -= t.m_value[i];
    }
    return value;
  }

  constexpr value_type operator[](const int dx) const { return m_value[dx]; }
  constexpr value_type get_x() const {
    static_assert(size >= 1);
    return m_value[0];
  }
  constexpr value_type get_y() const {
    static_assert(size >= 2);
    return m_value[1];
  }
  constexpr value_type get_z() const {
    static_assert(size == 3);
    return m_value[2];
  }
  constexpr value_type get_w() const {
    static_assert(size == 4);
    return m_value[3];
  }

private:
  std::array<value_type, n> m_value;
};

using point3 = tripple<twouble, 3>;
using point4 = tripple<twouble, 4>;
using vector3 = tripple<twouble, 3>;
using vector4 = tripple<twouble, 4>;
using color3 = tripple<color_t, 3>;
using spectra3 = tripple<twouble, 3>;

} // namespace twenty
