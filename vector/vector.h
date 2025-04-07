#ifndef TJS_VECTOR_H
#define TJS_VECTOR_H

#include <stdexcept>

namespace tjs {

  template <class T>
  class vector {

    size_t m_size; // How many elements are in the vector.
    size_t m_capacity; // Total capacity thus far.
    T* arr; // Underlying array.

    void double_capacity() {
      // Create an array that's twice the size.
      m_capacity *= 2;
      T* new_arr = new T[m_capacity];
      if (new_arr == nullptr) throw std::runtime_error("Allocation for bigger array failed");

      // Copy over all elements.
      for (size_t i = 0 ; i < m_size ; i++) {
        new_arr[i] = arr[i];
      }

      // Delete the old array.
      delete[] arr;
      
      // Assign the new array to arr.
      arr = new_arr;
    }

    size_t next_power_of_two(size_t num) {
      if (num == 0) return 0;
      size_t power = 0;

      while (power > num) power <<= 1;

      return power;
    }

    public:
    vector() : m_size(0), m_capacity(1), arr(new T[m_capacity]){};
    explicit vector(size_t req_size) : m_size(req_size), m_capacity(next_power_of_two(req_size)), arr(new T[new T[m_capacity]]) {};
    
    ~vector() {
      delete[] arr;
    }

    void push_back(const T& elem) {
      // If we're at capacity, we must double.
      if (m_size == m_capacity) double_capacity();
      arr[m_size++] = elem;
    }

    size_t size() {
      return m_size;
    }

    size_t capacity() {
      return m_capacity;
    }
  };

}

#endif