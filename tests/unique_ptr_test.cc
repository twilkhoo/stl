// tjs/unique_ptr_test.cc
#include "unique_ptr/unique_ptr.h"
#include <gtest/gtest.h>
#include <utility>  // for std::move

using tjs::unique_ptr;
using tjs::make_unique;

// A small helper type for operator-> tests
struct Foo {
  int x = 123;
  int get() const { return x; }
};

TEST(UniquePtrTest, DefaultConstructor) {
  unique_ptr<int> p;
  EXPECT_FALSE(p);
  EXPECT_EQ(p.get(), nullptr);
}

TEST(UniquePtrTest, PointerConstructorAndObservers) {
  unique_ptr<int> p(new int(42));
  EXPECT_TRUE(p);
  EXPECT_NE(p.get(), nullptr);
  EXPECT_EQ(*p, 42);
}

TEST(UniquePtrTest, OperatorArrow) {
  unique_ptr<Foo> p(new Foo());
  EXPECT_TRUE(p);
  EXPECT_EQ(p->get(), 123);
}

TEST(UniquePtrTest, Release) {
  unique_ptr<int> p(new int(7));
  int* raw = p.release();
  EXPECT_FALSE(p);
  EXPECT_EQ(*raw, 7);
  delete raw;  // caller reclaims ownership
}

TEST(UniquePtrTest, Reset) {
  unique_ptr<int> p(new int(10));
  p.reset(new int(20));
  EXPECT_TRUE(p);
  EXPECT_EQ(*p, 20);
  p.reset();
  EXPECT_FALSE(p);
  EXPECT_EQ(p.get(), nullptr);
}

TEST(UniquePtrTest, MoveConstructor) {
  unique_ptr<int> p(new int(1));
  unique_ptr<int> q(std::move(p));
  EXPECT_FALSE(p);
  EXPECT_TRUE(q);
  EXPECT_EQ(*q, 1);
}

TEST(UniquePtrTest, MoveAssignment) {
  unique_ptr<int> p(new int(2));
  unique_ptr<int> q;
  q = std::move(p);
  EXPECT_FALSE(p);
  EXPECT_TRUE(q);
  EXPECT_EQ(*q, 2);
}

TEST(UniquePtrTest, MakeUnique) {
  auto p = make_unique<std::pair<int, std::string>>(7, "foo");
  EXPECT_TRUE(p);
  EXPECT_EQ(p->first, 7);
  EXPECT_EQ(p->second, "foo");
}
