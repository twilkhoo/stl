#include "gtest/gtest.h"
#include "vector/vector.h"

TEST(VecTest, SizeChecks) {
  tjs::vector<int> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 1);

  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);

  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec.capacity(), 8);
}
