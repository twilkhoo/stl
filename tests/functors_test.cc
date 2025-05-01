#include "functors/functors.h"

#include <string>

#include "gtest/gtest.h"

using namespace tjs;

TEST(PlusFunctor, IntAddition) {
  plus<int> p;
  EXPECT_EQ(p(1, 2), 3);
}

TEST(MinusFunctor, DoubleSubtraction) {
  minus<double> m;
  EXPECT_DOUBLE_EQ(m(5.5, 2.0), 3.5);
}

TEST(PlusFunctorTransparent, MixedTypes) {
  plus<> p;
  EXPECT_DOUBLE_EQ(p(1, 2.5), 3.5);
}

TEST(MinusFunctorTransparent, MixedTypes) {
  minus<> m;
  EXPECT_FLOAT_EQ(m(5, 2.5f), 2.5f);
}

TEST(LessFunctor, IntComparison) {
  less<int> l;
  EXPECT_TRUE(l(1, 2));
  EXPECT_FALSE(l(2, 1));
}

TEST(GreaterFunctor, IntComparison) {
  greater<int> g;
  EXPECT_TRUE(g(2, 1));
  EXPECT_FALSE(g(1, 2));
}

TEST(LessFunctorTransparent, MixedTypes) {
  less<> l;
  EXPECT_TRUE(l(1, 2.5));
  EXPECT_FALSE(l(2.5, 1));
}

TEST(GreaterFunctorTransparent, MixedTypes) {
  greater<> g;
  EXPECT_TRUE(g(2.5, 1));
  EXPECT_FALSE(g(1, 2.5));
}

TEST(PlusFunctorStringConcat, RvalueLvalue) {
  plus<> p;
  std::string s1 = "foo";
  EXPECT_EQ(p(s1, std::string("bar")), "foobar");
}
