#include "gtest/gtest.h"

#include "color.h"

using namespace twenty;

TEST(Color, mono) {
  color3 x{100, 100, 100};

  ASSERT_EQ(15 + 70 + 15, mono(x));
}
