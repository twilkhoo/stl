#include "vector.h"

namespace tjs {

template <class T>
size_t vector<T>::next_power_of_two(size_t num) {
  if (num == 0) return 1;
  size_t power = 1;
  while (power < num) power <<= 1;
  return power;
}

template <class T>
void vector<T>::change_capacity(size_t n) {
  if (n <= m_capacity) return;

  // Set the new capacity.
  m_capacity = next_power_of_two(n);

  T* new_arr = new T[m_capacity];
  if (new_arr == nullptr)
    throw std::runtime_error("Allocation for bigger array failed");

  for (size_t i = 0; i < m_size; i++) {
    new_arr[i] = std::move(m_arr[i]);
  }
  delete[] m_arr;
  m_arr = new_arr;
}

template <class T>
void vector<T>::double_capacity() {
  change_capacity(m_capacity << 1);
}

// ------------------------------------------------------------------------
// Big 5
// ------------------------------------------------------------------------
template <class T>
vector<T>::vector() : m_size(0), m_capacity(1), m_arr(new T[m_capacity]) {}

template <class T>
vector<T>::vector(size_t req_size)
    : m_size(req_size),
      m_capacity(next_power_of_two(req_size)),
      m_arr(new T[m_capacity]()) {}

template <class T>
vector<T>::vector(std::initializer_list<T> l)
    : m_size(l.size()),
      m_capacity(next_power_of_two(m_size)),
      m_arr(new T[m_capacity]) {
  size_t i = 0;
  for (const auto& elem : l) {
    m_arr[i++] = elem;
  }
}

template <class T>
vector<T>::vector(const vector& other)
    : m_size(other.m_size),
      m_capacity(other.m_capacity),
      m_arr(new T[other.m_capacity]) {
  // std::cout << "Copy constructor\n";
  for (size_t i = 0; i < m_size; i++) {
    m_arr[i] = other.m_arr[i];
  }
}

template <class T>
vector<T>::vector(vector&& other)
    : m_size(other.m_size), m_capacity(other.m_capacity), m_arr(other.m_arr) {
  // std::cout << "Move constructor\n";
  other.m_arr = nullptr;
  other.m_size = 0;
  other.m_capacity = 0;
}

template <class T>
vector<T>& vector<T>::operator=(const vector& other) {
  if (this != &other) {
    delete[] m_arr;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_arr = new T[m_capacity];
    for (size_t i = 0; i < m_size; i++) {
      m_arr[i] = other.m_arr[i];
    }
  }
  return *this;
}

template <class T>
vector<T>& vector<T>::operator=(vector&& other) {
  if (this == &other) return *this;

  delete[] m_arr;
  m_arr = other.m_arr;
  m_size = other.m_size;
  m_capacity = other.m_capacity;
  other.m_arr = nullptr;
  other.m_size = 0;
  other.m_capacity = 0;
  return *this;
}

template <class T>
vector<T>::~vector() {
  delete[] m_arr;
}

// ------------------------------------------------------------------------
// Other Member Functions
// ------------------------------------------------------------------------

template <class T>
void vector<T>::push_back(const T& elem) {
  if (m_size == m_capacity) double_capacity();
  m_arr[m_size++] = elem;
}

template <class T>
template <typename... Args>
void vector<T>::emplace_back(Args&&... args) {
  if (m_size == m_capacity) double_capacity();

  m_arr[m_size++] = T(std::forward<Args>(args)...);
}

template <class T>
size_t vector<T>::size() const {
  return m_size;
}

template <class T>
size_t vector<T>::capacity() const {
  return m_capacity;
}

template <class T>
bool vector<T>::empty() const {
  return m_size == 0;
}

template <class T>
const T& vector<T>::operator[](size_t i) const {
  if (i >= m_size)
    throw std::out_of_range("Element " + std::to_string(i) +
                            " is out of range, vector has " +
                            std::to_string(m_size) + " elements.");
  return m_arr[i];
}

template <class T>
T& vector<T>::operator[](size_t i) {
  if (i >= m_size)
    throw std::out_of_range("Element " + std::to_string(i) +
                            " is out of range, vector has " +
                            std::to_string(m_size) + " elements.");
  return m_arr[i];
}

template <class T>
void vector<T>::reserve(size_t n) {
  change_capacity(n);
}

template <class U>
std::ostream& operator<<(std::ostream& os, const tjs::vector<U>& vec) {
  os << "{ ";
  for (size_t i = 0; i < vec.m_size; i++) {
    os << vec.m_arr[i] << " ";
  }
  os << "}";
  return os;
}

// ------------------------------------------------------------------------
// Iterator Implementations
// ------------------------------------------------------------------------

template <class T>
vector<T>::iterator::iterator(T* p) : ptr_(p) {}

template <class T>
typename vector<T>::iterator::reference vector<T>::iterator::operator*() const {
  return *ptr_;
}

template <class T>
typename vector<T>::iterator::pointer vector<T>::iterator::operator->() const {
  return ptr_;
}

template <class T>
typename vector<T>::iterator& vector<T>::iterator::operator++() {
  ++ptr_;
  return *this;
}

template <class T>
typename vector<T>::iterator vector<T>::iterator::operator++(int) {
  iterator tmp(*this);
  ++ptr_;
  return tmp;
}

template <class T>
typename vector<T>::iterator& vector<T>::iterator::operator--() {
  --ptr_;
  return *this;
}

template <class T>
typename vector<T>::iterator vector<T>::iterator::operator--(int) {
  iterator tmp(*this);
  --ptr_;
  return tmp;
}

template <class T>
typename vector<T>::iterator vector<T>::iterator::operator+(difference_type n) const {
  return iterator(ptr_ + n);
}

template <class T>
typename vector<T>::iterator vector<T>::iterator::operator-(difference_type n) const {
  return iterator(ptr_ - n);
}

template <class T>
typename vector<T>::iterator::difference_type vector<T>::iterator::operator-(
    const iterator& o) const {
  return ptr_ - o.ptr_;
}

template <class T>
typename vector<T>::iterator& vector<T>::iterator::operator+=(
    difference_type n) {
  ptr_ += n;
  return *this;
}

template <class T>
typename vector<T>::iterator& vector<T>::iterator::operator-=(
    difference_type n) {
  ptr_ -= n;
  return *this;
}

template <class T>
typename vector<T>::iterator::reference vector<T>::iterator::operator[](
    difference_type n) const {
  return *(ptr_ + n);
}

template <class T>
bool vector<T>::iterator::operator==(const iterator& o) const {
  return ptr_ == o.ptr_;
}

template <class T>
bool vector<T>::iterator::operator!=(const iterator& o) const {
  return ptr_ != o.ptr_;
}

template <class T>
bool vector<T>::iterator::operator<(const iterator& o) const {
  return ptr_ < o.ptr_;
}

template <class T>
bool vector<T>::iterator::operator>(const iterator& o) const {
  return ptr_ > o.ptr_;
}

template <class T>
bool vector<T>::iterator::operator<=(const iterator& o) const {
  return ptr_ <= o.ptr_;
}

template <class T>
bool vector<T>::iterator::operator>=(const iterator& o) const {
  return ptr_ >= o.ptr_;
}

template <class T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(m_arr);
}

template <class T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(m_arr + m_size);
}

}  // namespace tjs
