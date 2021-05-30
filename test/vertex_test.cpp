#include "gtest/gtest.h"

#include "vertex.h"

using namespace twenty;

TEST(Vertex3, ctor) {
  auto v3 = vertex3{{1, 2, 3}, {0, 0, 1}};
  ASSERT_EQ(point3(1, 2, 3), v3.position());
  ASSERT_EQ(spectra3(0, 0, 1), v3.spectra());
}

TEST(Vertex4, ctor) {
  auto v4 = vertex4{{1, 2, 3, 0.5}, {1, 0, 1}};
  ASSERT_EQ(point4(1, 2, 3, 0.5), v4.position());
  ASSERT_EQ(spectra3(1, 0, 1), v4.spectra());
}
