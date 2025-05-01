#ifndef TJS_STRING_H
#define TJS_STRING_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace tjs {

class string {
  // ------------------------------------------------------------------------
  // MEMBER VARIABLES
  // ------------------------------------------------------------------------

 public:
  static constexpr size_t SSO_BUFFER_SIZE = 16;
  static constexpr size_t npos = std::numeric_limits<size_t>::max();

 private:
  size_t m_size;
  size_t m_capacity;
  char* m_data;
  char m_sso_buffer[SSO_BUFFER_SIZE];

 public:
  // ------------------------------------------------------------------------
  // PRIVATE MEMBER FUNCTIONS
  // ------------------------------------------------------------------------
  bool is_sso();
  void allocate_heap(size_t count);
  void allocate_and_copy(const char* s, size_t count);

  // ------------------------------------------------------------------------
  // Big 5
  // ------------------------------------------------------------------------
  string();
  string(const string& other);
  string(string&& other);
  string(const string& other, size_t pos, size_t len = npos);
  string(const char* s);
  string(const char* s, size_t n);
  string(size_t n, char c);
  ~string();
  string& operator=(const string& other);
  string& operator=(string&& other);

  // ------------------------------------------------------------------------
  // Public Member Functions
  // ------------------------------------------------------------------------
  size_t size();
  size_t capacity();
  bool empty();
  void reserve(size_t new_cap);

  char& operator[](size_t pos);
  char& front();
  char& back();
  const char* c_str();

  void clear();
  void push_back(char c);
  void pop_back();
  string& append(const string& s);
  string& append(const char* s);
  string& append(const char* s, size_t n);
  string& operator+=(char c);
  string& operator+=(const string& s);

  string substr(size_t pos, size_t len = npos) const;

  // ------------------------------------------------------------------------
  // Iterator
  // ------------------------------------------------------------------------
  class iterator {
    char* ptr_;

   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = char;
    using difference_type = std::ptrdiff_t;
    using pointer = char*;
    using reference = char&;

    iterator(char* ptr = nullptr);
    reference operator*() const;
    pointer operator->() const;
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    iterator operator+(difference_type n) const;
    iterator operator-(difference_type n) const;
    difference_type operator-(const iterator& o) const;
    iterator& operator+=(difference_type n);
    iterator& operator-=(difference_type n);
    reference operator[](difference_type n) const;
    bool operator==(const iterator& o) const;
    bool operator!=(const iterator& o) const;
    bool operator<(const iterator& o) const;
    bool operator>(const iterator& o) const;
    bool operator<=(const iterator& o) const;
    bool operator>=(const iterator& o) const;
  };
  iterator begin();
  iterator end();
};

}  // namespace tjs

#include "string.tpp"
#endif  // TJS_STRING_H
