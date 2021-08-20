#pragma once

#include <list>

#include "patch.h"

namespace twenty {

class spatial_element {
public:
  using patch_list = std::list<patch4>;
  using iterator = patch_list::iterator;

  virtual iterator begin() = 0;

  virtual iterator end() = 0;
};

} // namespace twenty
