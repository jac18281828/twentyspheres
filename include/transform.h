#pragma once

#include "twenty.h"

namespace twenty {

class transform {
public:
  transform(vector3 const& scale, vector3 const& translate) : m_scale(scale), m_translate(translate) {}

  point3 operator()(point3 const& p) const {
    const auto scaled = vector3(p.get_x() * m_scale.get_x(), p.get_y() * m_scale.get_y(), p.get_z() * m_scale.get_z());

    const auto px = scaled + m_translate;
    return point3(px.get_x(), px.get_y(), px.get_z());
  }

private:
  vector3 m_scale;
  vector3 m_translate;
};
};

} // namespace twenty
