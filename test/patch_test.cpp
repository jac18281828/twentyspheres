#include "gtest/gtest.h"

#include "patch.h"
#include "tripple.h"
#include "twenty.h"

using namespace twenty;

TEST(Patch3, Build) {

  auto p1 = patch3::Builder().add(vertex3{{1, 2, 3}, {0, 1, 0}}).build();

  ASSERT_EQ(1, p1.size());

  auto s = p1.begin();
  ASSERT_EQ(point3(1, 2, 3), s->position());
  ASSERT_EQ(spectra3(0, 1, 0), s->spectra());
}
