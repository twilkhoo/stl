#include "unique_ptr.h"
#include <utility>

namespace tjs {

// ------------------------------------------------------------------------
// Big 5
// ------------------------------------------------------------------------

template <typename T>
unique_ptr<T>::unique_ptr() : m_ptr(nullptr) {}

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr) : m_ptr(ptr) {}

template <typename T>
unique_ptr<T>::~unique_ptr() {
  delete m_ptr;
}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& other) : m_ptr(other.m_ptr) {
  other.m_ptr = nullptr;
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& other) {
  if (this != &other) {
    delete m_ptr;
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
  }
  return *this;
}

// ------------------------------------------------------------------------
// Public Member Functions
// ------------------------------------------------------------------------

template <typename T>
T* unique_ptr<T>::get() const {
  return m_ptr;
}

template <typename T>
T& unique_ptr<T>::operator*() const {
  return *m_ptr;
}

template <typename T>
T* unique_ptr<T>::operator->() const {
  return m_ptr;
}

template <typename T>
unique_ptr<T>::operator bool() const {
  return m_ptr != nullptr;
}

template <typename T>
T* unique_ptr<T>::release() {
  T* temp = m_ptr;
  m_ptr = nullptr;
  return temp;
}

template <typename T>
void unique_ptr<T>::reset(T* ptr) {
  if (m_ptr != ptr) {
    delete m_ptr;
    m_ptr = ptr;
  }
}

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}  // namespace tjs
