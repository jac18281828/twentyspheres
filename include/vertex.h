#pragma once

#include "tripple.h"
#include "twenty.h"

namespace twenty {

template <typename value_type, int n> class vertex {
public:
  using point = tripple<value_type, n>;

  vertex() = default;

  vertex(point const& position, spectra3 const& spectra) : m_position(position), m_spectra(spectra) {}

  vertex(vertex const& v) = default;
  vertex(vertex&& v) = default;
  vertex& operator=(vertex const& v) = default;
  vertex& operator=(vertex&& v) = default;

  point const& position() const { return m_position; }

  spectra3 const& spectra() const { return m_spectra; }

private:
  tripple<value_type, n> m_position;
  spectra3 m_spectra;
};

using vertex3 = vertex<twouble, 3>;
using vertex4 = vertex<twouble, 4>;

} // namespace twenty
