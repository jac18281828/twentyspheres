#include "gtest/gtest.h"

#include "cube.h"
#include "twenty.h"

using namespace twenty;

TEST(Cube, Build) {
  auto c = cube(3, 3, 3, spectra3{1, 2, 3});
  ASSERT_EQ(6, std::distance(std::begin(c), std::end(c)));
}
