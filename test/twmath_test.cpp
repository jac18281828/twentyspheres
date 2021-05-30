#include <cmath>

#include "gtest/gtest.h"

#include "tripple.h"
#include "twenty.h"
#include "twmath.h"

using namespace twenty;

TEST(Vector, VectorPoint) {
  auto p1 = point3(1, 2, 3);
  auto v1 = vector(p1);

  ASSERT_NEAR(1, v1.get_x(), epsilon);
  ASSERT_NEAR(2, v1.get_y(), epsilon);
  ASSERT_NEAR(3, v1.get_z(), epsilon);
}

TEST(Vector, VectorDelta) {
  auto p1 = point3(0, 2, 3);
  auto p2 = point3(1, 2, 3);
  auto v1 = vector(p1, p2);

  ASSERT_NEAR(1, v1.get_x(), epsilon);
  ASSERT_NEAR(0, v1.get_y(), epsilon);
  ASSERT_NEAR(0, v1.get_z(), epsilon);
}

TEST(Vector, dot) {

  auto v1 = vector3(2, 2, 2);
  auto v2 = vector3(3, 2, 1);

  ASSERT_NEAR(12, dot(v1, v2), epsilon);
}

TEST(Vector, length) {
  auto v1 = vector3(3, 3, 3);

  ASSERT_NEAR(std::sqrt(27), length(v1), epsilon);
}

TEST(Vector, cross) {
  auto v1 = vector3(3, 2, 1);
  auto v2 = vector3(1, 2, 3);

  auto cr = cross(v1, v2);
  ASSERT_NEAR(4, cr.get_x(), epsilon);
  ASSERT_NEAR(-8, cr.get_y(), epsilon);
  ASSERT_NEAR(4, cr.get_z(), epsilon);
}

TEST(Math, sqr) { ASSERT_EQ(4, sqr<int>(2)); }

TEST(Vector, normal) {
  auto v1 = vector3(3, 3, 3);
  auto norm = normalize(v1);
  ASSERT_NEAR(1.0, length(norm), epsilon);
}

TEST(Vector, area) {

  auto v1 = vector({1, 0, 0});
  auto v2 = vector({0, 1, 0});

  ASSERT_NEAR(0.5, area(v1, v2), epsilon);
}
