// string.tpp
#include <cstring>

#include "string.h"

namespace tjs {

// ------------------------------------------------------------------------
// PRIVATE MEMBER FUNCTIONS
// ------------------------------------------------------------------------
bool string::is_sso() { return m_data == m_sso_buffer; }

void string::allocate_heap(size_t count) {
  m_capacity = count;
  m_data = new char[count + 1];
}

void string::allocate_and_copy(const char* s, size_t count) {
  if (count <= SSO_BUFFER_SIZE - 1) {
    m_data = m_sso_buffer;  // Use the SSO buffer.
    m_capacity = SSO_BUFFER_SIZE - 1;
  } else {
    allocate_heap(count);
  }
  std::memcpy(m_data, s, count);
  m_data[count] = '\0';  // Add the null terminator.
}

// ------------------------------------------------------------------------
// Big 5
// ------------------------------------------------------------------------
string::string() : m_size(0) {
  m_data = m_sso_buffer;
  m_capacity = SSO_BUFFER_SIZE - 1;
  m_sso_buffer[0] = '\0';
}

string::string(const string& other) : m_size(other.m_size) {
  allocate_and_copy(other.m_data, m_size);
}

string::string(string&& other) : m_size(other.m_size) {
  if (other.is_sso()) {
    m_data = m_sso_buffer;
    m_capacity = SSO_BUFFER_SIZE - 1;
    std::memcpy(m_sso_buffer, other.m_sso_buffer, m_size + 1);
  } else {
    m_data = other.m_data;
    m_capacity = other.m_capacity;
    other.m_data = other.m_sso_buffer;
    other.m_capacity = SSO_BUFFER_SIZE - 1;
  }
  other.m_size = 0;
  std::memset(other.m_sso_buffer, 0, other.SSO_BUFFER_SIZE);
}

string::string(const string& other, size_t pos, size_t len) : m_size(0) {
  if (pos < other.m_size) {
    size_t rlen =
        (len == npos ? other.m_size - pos : std::min(len, other.m_size - pos));
    allocate_and_copy(other.m_data + pos, rlen);
    m_size = rlen;
  } else {
    m_data = m_sso_buffer;
    m_capacity = SSO_BUFFER_SIZE - 1;
    m_sso_buffer[0] = '\0';
  }
}

string::string(const char* s) : m_size(std::strlen(s)) {
  allocate_and_copy(s, m_size);
}

string::string(const char* s, size_t n) : m_size(n) { allocate_and_copy(s, n); }

string::string(size_t n, char c) : m_size(n) {
  if (n <= SSO_BUFFER_SIZE - 1) {
    m_data = m_sso_buffer;
    m_capacity = SSO_BUFFER_SIZE - 1;
  } else {
    allocate_heap(n);
  }
  std::fill_n(m_data, n, c);
  m_data[n] = '\0';
}

string::~string() {
  if (!is_sso()) delete[] m_data;
}

string& string::operator=(const string& other) {
  if (this != &other) {
    if (!is_sso()) ::operator delete(m_data);
    m_size = other.m_size;
    allocate_and_copy(other.m_data, m_size);
  }
  return *this;
}

string& string::operator=(string&& other) {
  if (this != &other) {
    if (!is_sso()) ::operator delete(m_data);
    if (other.is_sso()) {
      m_data = m_sso_buffer;
      m_capacity = SSO_BUFFER_SIZE - 1;
      std::memcpy(m_sso_buffer, other.m_sso_buffer, other.m_size + 1);
    } else {
      m_data = other.m_data;
      m_capacity = other.m_capacity;
    }
    m_size = other.m_size;
    other.m_data = other.m_sso_buffer;
    other.m_capacity = SSO_BUFFER_SIZE - 1;
    other.m_size = 0;
    other.m_sso_buffer[0] = '\0';
  }
  return *this;
}

// ------------------------------------------------------------------------
// Other Member Functions
// ------------------------------------------------------------------------
size_t string::size() { return m_size; }
size_t string::capacity() { return m_capacity; }
bool string::empty() { return m_size == 0; }

void string::reserve(size_t new_cap) {
  if (new_cap <= m_capacity) return;
  char* old_data = m_data;
  size_t old_size = m_size;
  allocate_heap(new_cap);
  std::memcpy(m_data, old_data, old_size);
  m_data[old_size] = '\0';

  if (!(old_data == m_sso_buffer)) delete[] old_data;
}

// ———— ELEMENT ACCESS ————
char& string::operator[](size_t pos) {
  if (pos >= m_size) throw std::out_of_range("string::at");
  return m_data[pos];
}
char& string::front() { return m_data[0]; }
char& string::back() { return m_data[m_size - 1]; }
const char* string::c_str() { return m_data; }

void string::clear() {
  m_size = 0;
  m_data[0] = '\0';
}

void string::push_back(char c) {
  if (m_size + 1 > m_capacity) {
    reserve(std::max<size_t>(2 * m_capacity, 1));
  }
  m_data[m_size++] = c;
  m_data[m_size] = '\0';
}

void string::pop_back() {
  if (m_size > 0) {
    m_data[--m_size] = '\0';
  }
}

string& string::append(const char* s, size_t n) {
  if (m_size + n > m_capacity) {
    reserve(std::max(m_size + n, 2 * m_capacity));
  }
  std::memcpy(m_data + m_size, s, n);
  m_size += n;
  m_data[m_size] = '\0';
  return *this;
}

string& string::append(const string& s) { return append(s.m_data, s.m_size); }

string& string::append(const char* s) { return append(s, std::strlen(s)); }

string& string::operator+=(char c) {
  push_back(c);
  return *this;
}
string& string::operator+=(const string& s) { return append(s); }

string string::substr(size_t pos, size_t len) const {
  return string(*this, pos, len);
}

// ------------------------------------------------------------------------
// Iterator Implementations
// ------------------------------------------------------------------------

string::iterator::iterator(char* ptr) : ptr_(ptr) {}

string::iterator::reference string::iterator::operator*() const {
  return *ptr_;
}

string::iterator::pointer string::iterator::operator->() const { return ptr_; }

string::iterator& string::iterator::operator++() {
  ++ptr_;
  return *this;
}

string::iterator string::iterator::operator++(int) {
  iterator tmp(*this);
  ++ptr_;
  return tmp;
}

string::iterator& string::iterator::operator--() {
  --ptr_;
  return *this;
}

string::iterator string::iterator::operator--(int) {
  iterator tmp(*this);
  --ptr_;
  return tmp;
}

string::iterator string::iterator::operator+(difference_type n) const {
  return iterator(ptr_ + n);
}

string::iterator string::iterator::operator-(difference_type n) const {
  return iterator(ptr_ - n);
}

string::iterator::difference_type string::iterator::operator-(
    const iterator& o) const {
  return ptr_ - o.ptr_;
}

string::iterator& string::iterator::operator+=(difference_type n) {
  ptr_ += n;
  return *this;
}

string::iterator& string::iterator::operator-=(difference_type n) {
  ptr_ -= n;
  return *this;
}

string::iterator::reference string::iterator::operator[](
    difference_type n) const {
  return *(ptr_ + n);
}

bool string::iterator::operator==(const iterator& o) const {
  return ptr_ == o.ptr_;
}

bool string::iterator::operator!=(const iterator& o) const {
  return ptr_ != o.ptr_;
}

bool string::iterator::operator<(const iterator& o) const {
  return ptr_ < o.ptr_;
}

bool string::iterator::operator>(const iterator& o) const {
  return ptr_ > o.ptr_;
}

bool string::iterator::operator<=(const iterator& o) const {
  return ptr_ <= o.ptr_;
}

bool string::iterator::operator>=(const iterator& o) const {
  return ptr_ >= o.ptr_;
}

string::iterator string::begin() { return iterator(m_data); }

string::iterator string::end() { return iterator(m_data + m_size); }

}  // namespace tjs
