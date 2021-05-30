#pragma once

#include <list>

#include "patch.h"
#include "spatial.h"
#include "twenty.h"

namespace twenty {

class cube : public spatial {
public:
  cube(twouble const w, twouble const h, twouble const d, spectra3 const& color) {

    // 6 faces

    const auto anchor = point3{0, 0, 0};
    const auto up = point3{0, h, 0};
    const auto right = point3{w, 0, 0};
    const auto back = point3{0, 0, d};

    const auto v11 = vertex3(anchor, color);
    const auto v12 = vertex3(anchor + up, color);
    const auto v13 = vertex3(anchor + right, color);
    const auto v14 = vertex3(anchor + right + up, color);
    const auto v21 = vertex3(anchor + back, color);
    const auto v22 = vertex3(anchor + up + back, color);
    const auto v23 = vertex3(anchor + right + back, color);
    const auto v24 = vertex3(anchor + right + up + back, color);

    // front, back, left, right, top, bottom
    const auto p1 = patch4::Builder().add(v11).add(v12).add(v13).add(v14).build();
    m_space.emplace_back(std::move(p1));
    const auto p2 = patch4::Builder().add(v21).add(v22).add(v23).add(v24).build();
    m_space.emplace_back(std::move(p2));
    const auto p3 = patch4::Builder().add(v11).add(v12).add(v21).add(v22).build();
    m_space.emplace_back(std::move(p3));
    const auto p4 = patch4::Builder().add(v13).add(v14).add(v23).add(v24).build();
    m_space.emplace_back(std::move(p4));
    const auto p5 = patch4::Builder().add(v12).add(v14).add(v22).add(v24).build();
    m_space.emplace_back(std::move(p5));
    const auto p6 = patch4::Builder().add(v11).add(v13).add(v21).add(v23).build();
    m_space.emplace_back(std::move(p6));
  }

  virtual iterator begin() override { return std::begin(m_space); }

  virtual iterator end() override { return std::end(m_space); }

private:
  patch_list m_space;
};

} // namespace twenty
