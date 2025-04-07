#include "gtest/gtest.h"
#include "vector/vector.h"

TEST(ObjectTest, ReturnsTheAnswer) {
  tjs::vector vec;
  EXPECT_EQ(vec.test(), 42);
}
