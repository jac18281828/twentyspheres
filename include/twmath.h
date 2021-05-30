#pragma once

#include <cmath>

#include "tripple.h"

namespace twenty {

constexpr vector3 vector(point3 const& p1) { return vector3(p1); }

constexpr vector3 vector(point3 const& p1, point3 const& p2) {
  return vector3(p2.get_x() - p1.get_x(), p2.get_y() - p1.get_y(), p2.get_z() - p1.get_z());
}

template <typename value_type = twouble, int n = 3>
constexpr value_type dot(tripple<value_type, n> const& v1, tripple<value_type, n> const& v2) {

  static_assert(v1.size == v2.size);
  value_type sum = 0;
  for (int i = 0; i < v1.size; ++i) {
    sum += v1[i] * v2[i];
  }
  return sum;
}

constexpr vector3 cross(vector3 const& v1, vector3 const& v2) {
  const auto x = v1.get_y() * v2.get_z() - v1.get_z() * v2.get_y();
  const auto y = v1.get_z() * v2.get_x() - v1.get_x() * v2.get_z();
  const auto z = v1.get_x() * v2.get_y() - v1.get_y() * v2.get_x();
  return vector3(x, y, z);
}

constexpr twouble length(vector3 const& v) { return std::sqrt(dot(v, v)); }

constexpr vector3 normalize(vector3 const& v) {
  const auto len = length(v);
  return vector3(v.get_x() / len, v.get_y() / len, v.get_z() / len);
}

constexpr twouble area(vector3 const& v1, vector3 const& v2) {
  auto crs = cross(v1, v2);
  return length(crs) / 2.0;
}

template <typename value_t = twouble> constexpr value_t sqr(const value_t x) { return x * x; }

} // namespace twenty
