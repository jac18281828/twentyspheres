#pragma once

#include <array>
#include <exception>
#include <iterator>

#include "tripple.h"
#include "twenty.h"
#include "vertex.h"

namespace twenty {

template <typename value_type, int n, int d = 3> class patch {
public:
  using vert = vertex<value_type, d>;
  using patch_array = std::array<vert, n>;

private:
  patch(patch_array const& patch, const int size) : m_patch(patch), m_size(size) {}

public:
  patch() = default;

  patch(patch const& p) = default;
  patch(patch&& p) = default;

  patch(patch_array const& patch) : m_patch(patch), m_size(patch.size()) {}
  patch(patch_array&& patch) : m_patch(std::move(patch.m_patch)), m_size(patch.size()) {}

  patch& operator=(patch const& p) = default;
  patch& operator=(patch&& p) = default;

  auto begin() { return std::begin(m_patch); }

  auto end() { return std::end(m_patch); }

  size_t size() const { return m_size; }

  class Builder final {
  public:
    Builder() {
      m_iter = std::begin(m_patch);
      m_size = 0;
    }

    Builder& add(vert const& p) {
      if (m_iter != std::end(m_patch)) {
        *m_iter = p;
        ++m_iter;
        m_size++;
        return *this;
      } else {
        throw std::runtime_error("Too many points for patch");
      }
    }

    patch build() const { return patch(m_patch, m_size); }

  private:
    patch_array::iterator m_iter;
    patch_array m_patch;
    size_t m_size;
  };

private:
  patch_array m_patch;
  size_t m_size;
};

using patch3 = patch<twouble, 3>;
using patch4 = patch<twouble, 4>;

} // namespace twenty
