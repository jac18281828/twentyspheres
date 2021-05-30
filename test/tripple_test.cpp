#include "gtest/gtest.h"

#include "tripple.h"
#include "twenty.h"
#include "twmath.h"

using namespace twenty;

TEST(Point3, Ctor) {

  auto p1 = point3(1, 2, 3);

  ASSERT_NEAR(1, p1.get_x(), epsilon);
  ASSERT_NEAR(2, p1.get_y(), epsilon);
  ASSERT_NEAR(3, p1.get_z(), epsilon);
}

TEST(Point3, assign) {
  auto p1 = point3(1, 2, 3);
  auto p2 = p1;

  ASSERT_NEAR(1, p2.get_x(), epsilon);
  ASSERT_NEAR(2, p2.get_y(), epsilon);
  ASSERT_NEAR(3, p2.get_z(), epsilon);
}

TEST(Point3, movector) {
  auto p1 = point3(1, 2, 3);
  auto p2 = point3(std::move(p1));

  ASSERT_NEAR(1, p2.get_x(), epsilon);
  ASSERT_NEAR(2, p2.get_y(), epsilon);
  ASSERT_NEAR(3, p2.get_z(), epsilon);
}

TEST(Point3, move) {
  auto p1 = point3(1, 2, 3);
  auto p2 = std::move(p1);

  ASSERT_NEAR(1, p2.get_x(), epsilon);
  ASSERT_NEAR(2, p2.get_y(), epsilon);
  ASSERT_NEAR(3, p2.get_z(), epsilon);
}

TEST(Vector3, DefaultZero) {
  auto v1 = vector3();
  ASSERT_NEAR(0, length(v1), epsilon);
}

TEST(Vector3, Addition) {
  const auto v1 = vector3{{1, 2, 3}};
  const auto v2 = vector3{{2, 3, 4}};

  const auto sum = vector3{{3, 5, 7}};

  ASSERT_EQ(sum, v1 + v2);
}

TEST(Vector4, Addition) {
  const auto v1 = vector4{{1, 2, 3, 4}};
  const auto v2 = vector4{{2, 3, 4, 5}};

  const auto sum = vector4{{3, 5, 7, 9}};

  ASSERT_EQ(sum, v1 + v2);
}

TEST(Vector3, Subtraction) {
  const auto v1 = vector3{{1, 2, 3}};
  const auto v2 = vector3{{2, 3, 4}};

  const auto diff = vector3{{1, 1, 1}};

  ASSERT_EQ(diff, v2 - v1);
}

TEST(Vector4, Subtraction) {
  const auto v1 = vector4{{1, 2, 3, 4}};
  const auto v2 = vector4{{2, 3, 4, 5}};

  const auto diff = vector4{{1, 1, 1, 1}};

  ASSERT_EQ(diff, v2 - v1);
}
