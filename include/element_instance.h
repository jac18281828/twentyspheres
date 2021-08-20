#pragma once

#include <memory>

#include "spatial"
#include "transform"

namespace twenty {

class element_instance {
public:
  element_instance(std::shared_ptr<spatial_element> instance, transform const& transform)
      : m_instance(instance), m_transform(transform) {}

  std::list<patch4> get_patch_list() const {
    std::list<patch4> plist;
    for (auto start = std::begin(*m_instance); start != std::end(*m_instance); ++start) {
      auto builder = patch4::Builder();
      builder.add(m_transform(*start));
      plist.push_back(builder.build());
    }
    return plist;
  }

private:
  std::shared_ptr<spatial_element> m_instance;
  transform m_transform;
}

} // namespace twenty
