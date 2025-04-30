#include "vector/vector.h"

#include <numeric>
#include <string>
#include <utility>

#include "gtest/gtest.h"

using tjs::vector;

static vector<int> make_seq(int n) {
  vector<int> v;
  for (int i = 0; i < n; i++) v.push_back(i);
  return v;
}

TEST(VecTest, PushBackSizeCapacity) {
  vector<int> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 1);

  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.emplace_back(4);
  vec.emplace_back(5);

  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec.capacity(), 8);
}

TEST(VecTest, DefaultEmptyAndReserve) {
  vector<int> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 1);

  v.reserve(10);
  EXPECT_GE(v.capacity(), 10);
  EXPECT_EQ(v.size(), 0);
  EXPECT_TRUE(v.empty());

  size_t old_cap = v.capacity();
  v.reserve(old_cap - 1);
  EXPECT_EQ(v.capacity(), old_cap);
}

TEST(VecTest, InitializerListConstructor) {
  vector<int> v{10, 20, 30};
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
  EXPECT_EQ(v.capacity(), 4u);
}

TEST(VecTest, PushBackAndOperatorAt) {
  vector<int> v = make_seq(8);
  EXPECT_EQ(v.size(), 8u);
  for (size_t i = 0; i < v.size(); i++) EXPECT_EQ(v[i], i);
}

TEST(VecTest, CopyConstructorAndAssignment) {
  vector<int> orig = make_seq(5);

  vector<int> copy(orig);
  EXPECT_EQ(copy.size(), orig.size());
  EXPECT_EQ(copy.capacity(), orig.capacity());

  for (size_t i = 0; i < orig.size(); ++i) EXPECT_EQ(copy[i], orig[i]);

  orig[2] = 999;
  EXPECT_EQ(copy[2], 2);

  vector<int> assigned;
  assigned = orig;
  EXPECT_EQ(assigned.size(), orig.size());
  EXPECT_EQ(assigned[2], 999);
}

TEST(VecTest, MoveConstructorAndAssignment) {
  vector<int> temp = make_seq(6);
  size_t origCap = temp.capacity();

  vector<int> moved(std::move(temp));
  EXPECT_EQ(moved.size(), 6u);
  EXPECT_EQ(moved.capacity(), origCap);
  for (int i = 0; i < 6; ++i) EXPECT_EQ(moved[i], i);

  EXPECT_EQ(temp.size(), 0u);

  vector<int> another;
  another = std::move(moved);
  EXPECT_EQ(another.size(), 6u);
  EXPECT_EQ(another.capacity(), origCap);
  for (int i = 0; i < 6; ++i) EXPECT_EQ(another[i], i);
}

TEST(VecTest, EmplaceBackComplexType) {
  vector<std::pair<std::string, int>> vp;
  vp.emplace_back("hello", 42);
  vp.emplace_back("world", 7);

  EXPECT_EQ(vp.size(), 2u);
  EXPECT_EQ(vp[0].first, "hello");
  EXPECT_EQ(vp[0].second, 42);
  EXPECT_EQ(vp[1].first, "world");
  EXPECT_EQ(vp[1].second, 7);
}

TEST(VecTest, IteratorTraversalAndArithmetic) {
  vector<int> v = make_seq(5);  // [0,1,2,3,4]

  int sum = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, std::accumulate(v.begin(), v.end(), 0));

  // Random access.
  auto it = v.begin();
  EXPECT_EQ(*(it + 2), 2);
  it += 4;
  EXPECT_EQ(*it, 4);
  EXPECT_EQ(*(v.end() - 1), 4);

  // Difference.
  EXPECT_EQ(v.end() - v.begin(), static_cast<std::ptrdiff_t>(v.size()));

  // Comparisons.
  EXPECT_TRUE(v.begin() < v.end());
  EXPECT_TRUE(v.begin() <= v.begin());
  EXPECT_TRUE(v.end() > v.begin());
  EXPECT_TRUE(v.end() >= v.end());
}

TEST(VecTest, RangeForSupport) {
  vector<int> v = make_seq(4);
  int expected = 0;
  for (int x : v) EXPECT_EQ(x, expected++);

  EXPECT_EQ(expected, 4);
}
