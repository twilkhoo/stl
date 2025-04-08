#ifndef TJS_VECTOR_H
#define TJS_VECTOR_H

#include <iostream>
#include <stdexcept>

namespace tjs {

template <class T>
class vector {
  // ------------------------------------------------------------------------
  //
  // MEMBER VARIABLES
  //
  // ------------------------------------------------------------------------

  size_t m_size;      // How many elements are in the vector.
  size_t m_capacity;  // Total capacity thus far.
  T* m_arr;             // Underlying array.

  // ------------------------------------------------------------------------
  //
  // PRIVATE MEMBER FUNCTIONS
  //
  // ------------------------------------------------------------------------

  void double_capacity() {
    // Create an array that's twice the size.
    m_capacity *= 2;
    T* new_arr = new T[m_capacity];
    if (new_arr == nullptr)
      throw std::runtime_error("Allocation for bigger array failed");

    // Copy over all elements.
    for (size_t i = 0; i < m_size; i++) {
      new_arr[i] = m_arr[i];
    }

    // Delete the old array.
    delete[] m_arr;

    // Assign the new array to m_arr.
    m_arr = new_arr;
  }

  size_t next_power_of_two(size_t num) {
    if (num == 0) return 0;
    size_t power = 1;
    while (power < num) power <<= 1;
    return power;
  }

  // ------------------------------------------------------------------------
  //
  // PUBLIC MEMBER FUNCTIONS
  //
  // ------------------------------------------------------------------------

 public:
  // ------------------------------------------------------------------------
  // Big 5
  // ------------------------------------------------------------------------

  // Default constructor (no args).
  vector() : m_size(0), m_capacity(1), m_arr(new T[m_capacity]) {};

  // Constructor with just size specified.
  explicit vector(size_t req_size)
      : m_size(req_size),
        m_capacity(next_power_of_two(req_size)),
        m_arr(new T[m_capacity]) {};

  // Constructor with initializer list.
  explicit vector(std::initializer_list<T> l)
      : m_size(l.size()),
        m_capacity(next_power_of_two(m_size)),
        m_arr(new T[m_capacity]) {
    for (size_t i = 0; i < l.size(); i++) m_arr[i] = *(l.begin() + i);
  }

  // Copy constructor.
  vector(const vector& other)
      : m_size(other.size()),
        m_capacity(other.capacity()),
        m_arr(new T[m_capacity]) {
    std::cout << "Copy constructor\n";
    for (size_t i = 0; i < other.size(); i++) m_arr[i] = other[i];
  }

  // Move constructor.
  vector(vector&& other) : m_size(other.size()), m_capacity(other.capacity()), m_arr(other.m_arr) {
    std::cout << "Move constructor\n";
    other.m_arr = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
  }

  // Copy assignment operator.
  vector& operator=(const vector& other) {
    // Transfer the sizes.
    m_size = other.m_size;
    m_capacity= other.m_capacity;
    m_arr = new T[m_capacity];

    for (size_t i = 0; i < other.size(); i++) m_arr[i] = other[i];
  }

  // Move assignment operator.
  vector& operator=(vector&& other) {
    if (this == &other) return this;

    // Free existing array.
    delete[] m_arr;

    // Transfer the data pointer and sizes.
    m_arr = other.m_arr;
    m_size = other.m_size;
    m_capacity= other.m_capacity;

    // Reset the source object.
    other.m_arr = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
    return *this;
  }

  // Destructor.
  ~vector() { delete[] m_arr; }

  // ------------------------------------------------------------------------
  // Other functions
  // ------------------------------------------------------------------------

  void push_back(const T& elem) {
    // If we're at capacity, we must double.
    if (m_size == m_capacity) double_capacity();
    m_arr[m_size++] = elem;
  }

  size_t size() const { return m_size; }

  size_t capacity() const { return m_capacity; }

  bool empty() { return m_size == 0; }

  T operator[](size_t i) const {
    if (i >= m_size)
      throw std::out_of_range("Element " + std::to_string(i) +
                              " is out of range, vector has " +
                              std::to_string(m_size) + " elements.");
    return m_arr[i];
  }

  friend std::ostream& operator<<(std::ostream& os, const tjs::vector<T>& vec) {
    os << "{ ";
    for (size_t i = 0; i < vec.size(); i++) {
      os << vec[i] << " ";
    }
    os << "}";
    return os;
  }
};

}  // namespace tjs

#endif