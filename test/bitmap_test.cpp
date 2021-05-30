#include "gtest/gtest.h"

#include "bitmap.h"
#include "color.h"

using namespace twenty;

TEST(Bitmap, fill) {

  bitmap bm(20, 20);

  auto c = color3(3, 2, 1);

  bm.fill(c);

  auto buffer = bm.buffer();

  for (int i = 0; i < buffer.size(); ++i) {
    ASSERT_EQ(c[i % 3], buffer[i]);
  }
}
