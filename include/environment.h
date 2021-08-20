#pragma once

#include <list>

#include "element_instance.h"

namespace twenty {

class environment {
public:
  using instance_list = std::list<element_instance>;
  using iterator = instance_list::iterator;

  environment() = default;

  void add(element_instance const& instance) { m_instance_list.push_back(instance); }

  iterator begin() { return m_instance_list.begin(); }
  iterator end() { return m_instance_list.end(); }

private:
  instance_list m_instance_list;
}

} // namespace twenty
