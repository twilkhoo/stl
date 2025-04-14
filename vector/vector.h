#ifndef TJS_VECTOR_H
#define TJS_VECTOR_H

#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>

namespace tjs {

template <class T>
class vector {
  // ------------------------------------------------------------------------
  // MEMBER VARIABLES
  // ------------------------------------------------------------------------
  size_t m_size;      // How many elements are in the vector.
  size_t m_capacity;  // Total capacity thus far.
  T* m_arr;           // Underlying array.

  // ------------------------------------------------------------------------
  // PRIVATE MEMBER FUNCTIONS
  // ------------------------------------------------------------------------
  void change_capacity(size_t n);
  void double_capacity();
  size_t next_power_of_two(size_t num);

 public:
  // ------------------------------------------------------------------------
  // Big 5
  // ------------------------------------------------------------------------
  vector();
  explicit vector(size_t req_size);
  explicit vector(std::initializer_list<T> l);
  vector(const vector& other);
  vector(vector&& other);
  vector& operator=(const vector& other);
  vector& operator=(vector&& other);
  ~vector();

  // ------------------------------------------------------------------------
  // Public Member Functions
  // ------------------------------------------------------------------------
  void push_back(const T& elem);
  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  void reserve(size_t n);

  // Operator [] overloads.
  const T& operator[](size_t i) const;
  T& operator[](size_t i);

  // Output operator overload.
  template <class U>
  friend std::ostream& operator<<(std::ostream& os, const tjs::vector<U>& vec);
};

}  // namespace tjs

#include "vector.tpp"
#endif  // TJS_VECTOR_H
