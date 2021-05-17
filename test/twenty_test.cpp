#include "gtest/gtest.h"

#include "color.h"

using namespace twenty;

TEST(Color, sqr) { ASSERT_EQ(4, sqr<int>(2)); }

TEST(Color, mono) {
  point<color_t> x{100, 100, 100};

  ASSERT_EQ(15 + 70 + 15, mono(x));
}

TEST(Color, write_pixel) {

  screenbuffer_t buffer;

  buffer.resize(300);

  std::fill(std::begin(buffer), std::end(buffer), 0);

  write_pixel(buffer, {0, 1}, 30, {1, 2, 3});

  const auto offset = 30 * depth;

  ASSERT_EQ(1, buffer[offset]);
  ASSERT_EQ(2, buffer[offset + 1]);
  ASSERT_EQ(3, buffer[offset + 2]);
}
