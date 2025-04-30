#include "../string/string.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <stdexcept>

using tjs::string;

static string make_alpha(size_t n) {
  string s;
  for (size_t i = 0; i < n; ++i) {
    s.push_back(char('a' + (i % 26)));
  }
  return s;
}

TEST(StringTest, DefaultConstructorAndEmpty) {
  string s;
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
  EXPECT_STREQ(s.c_str(), "");
  // Capacity should be at least SSO_BUFFER_SIZE-1
  EXPECT_GE(s.capacity(), string::SSO_BUFFER_SIZE - 1);
}

TEST(StringTest, FromCStringAndSize) {
  string s("hello");
  EXPECT_EQ(s.size(), 5u);
  EXPECT_STREQ(s.c_str(), "hello");

  string empty("");
  EXPECT_EQ(empty.size(), 0u);
  EXPECT_STREQ(empty.c_str(), "");
}

TEST(StringTest, CopyAndModify) {
  string orig("copy me");
  string cpy(orig);
  EXPECT_EQ(cpy.size(), orig.size());
  EXPECT_STREQ(cpy.c_str(), orig.c_str());

  cpy[0] = 'C';
  EXPECT_EQ(orig[0], 'c');  // original unchanged
  EXPECT_EQ(cpy[0], 'C');
}

TEST(StringTest, MoveConstructorLeavesSourceEmpty) {
  string tmp("move me");
  size_t old_cap = tmp.capacity();
  string moved(std::move(tmp));

  EXPECT_EQ(moved.size(), 7u);
  EXPECT_STREQ(moved.c_str(), "move me");
  EXPECT_EQ(moved.capacity(), old_cap);

  EXPECT_EQ(tmp.size(), 0u);
  EXPECT_STREQ(tmp.c_str(), "");
}

TEST(StringTest, SubstringConstructorAndSubstrMethod) {
  string base("hello world");
  // ctor version:
  string sub1(base, 6, 5);
  EXPECT_EQ(sub1.size(), 5u);
  EXPECT_STREQ(sub1.c_str(), "world");

  string sub2(base, 3);  // len = npos → to end
  EXPECT_EQ(sub2.size(), 8u);
  EXPECT_STREQ(sub2.c_str(), "lo world");

  // member substr():
  auto sub3 = base.substr(0, 5);
  EXPECT_STREQ(sub3.c_str(), "hello");
  auto sub4 = base.substr(4);
  EXPECT_STREQ(sub4.c_str(), "o world");
}

TEST(StringTest, FromBufferAndFillCtor) {
  const char raw[] = "abcdefgh";
  string buf(raw, 3);
  EXPECT_EQ(buf.size(), 3u);
  EXPECT_STREQ(buf.c_str(), "abc");

  string fill(5, 'x');
  EXPECT_EQ(fill.size(), 5u);
  EXPECT_STREQ(fill.c_str(), "xxxxx");
}

TEST(StringTest, PushPopAndClear) {
  string s;
  s.push_back('a');
  s.push_back('b');
  EXPECT_EQ(s.size(), 2u);
  EXPECT_STREQ(s.c_str(), "ab");

  s.pop_back();
  EXPECT_EQ(s.size(), 1u);
  EXPECT_STREQ(s.c_str(), "a");

  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_STREQ(s.c_str(), "");
}

TEST(StringTest, AppendAndOperatorPlusEquals) {
  string a("foo"), b("bar");
  a.append(b);
  EXPECT_STREQ(a.c_str(), "foobar");

  a.append("baz");
  EXPECT_STREQ(a.c_str(), "foobarbaz");

  a += '!';
  EXPECT_STREQ(a.c_str(), "foobarbaz!");

  a += b;
  EXPECT_STREQ(a.c_str(), "foobarbaz!bar");
}

TEST(StringTest, Reserve) {
  string s = make_alpha(10);
  s.reserve(100);
  EXPECT_GE(s.capacity(), 100u);
  EXPECT_EQ(s.size(), 10u);
}

TEST(StringTest, AtBoundsChecking) {
  string s("bounds");
  EXPECT_NO_THROW(s[0]);
  EXPECT_NO_THROW(s[5]);
  EXPECT_THROW(s[6], std::out_of_range);
}

TEST(StringTest, IteratorTraversalAndRandomAccess) {
  string s("abcde");  // size = 5
  // sum via iterator
  std::string stds = s.c_str();  // helper
  char captured[6] = {};
  size_t idx = 0;
  for (auto it = s.begin(); it != s.end(); ++it, ++idx) {
    captured[idx] = *it;
  }
  EXPECT_STREQ(captured, "abcde");
  EXPECT_EQ(idx, s.size());

  // random access arithmetic
  auto it = s.begin();
  EXPECT_EQ(*(it + 2), 'c');
  it += 4;
  EXPECT_EQ(*it, 'e');
  EXPECT_EQ(*(s.end() - 1), 'e');

  EXPECT_EQ(s.end() - s.begin(), static_cast<std::ptrdiff_t>(s.size()));
  EXPECT_TRUE(s.begin() < s.end());
  EXPECT_TRUE(s.begin() <= s.begin());
  EXPECT_TRUE(s.end() > s.begin());
  EXPECT_TRUE(s.end() >= s.end());
}

TEST(StringTest, RangeForLoop) {
  string s("xyz");
  std::string result;
  for (char c : s) result.push_back(c);
  EXPECT_EQ(result, "xyz");
}

TEST(StringTest, CopyAssignmentAndMoveAssignment) {
  string a("assign");
  string b;
  b = a;
  EXPECT_EQ(b.size(), a.size());
  EXPECT_STREQ(b.c_str(), "assign");

  string c;
  c = std::move(b);
  EXPECT_EQ(c.size(), 6u);
  EXPECT_STREQ(c.c_str(), "assign");
  EXPECT_EQ(b.size(), 0u);
  EXPECT_STREQ(b.c_str(), "");
}
