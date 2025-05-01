// unique_ptr.h
#ifndef TJS_UNIQUE_PTR_H
#define TJS_UNIQUE_PTR_H

namespace tjs {

template <typename T>
class unique_ptr {
  // ------------------------------------------------------------------------
  // MEMBER VARIABLES
  // ------------------------------------------------------------------------
  T* m_ptr;

 public:
  // ------------------------------------------------------------------------
  // Big 5
  // ------------------------------------------------------------------------
  unique_ptr();
  explicit unique_ptr(T* ptr);
  ~unique_ptr();

  unique_ptr(unique_ptr&& other);
  unique_ptr& operator=(unique_ptr&& other);

  // Delete the copy constructor/assignment operators.
  unique_ptr(const unique_ptr&) = delete;
  unique_ptr& operator=(const unique_ptr&) = delete;

  // ------------------------------------------------------------------------
  // Public Member Functions
  // ------------------------------------------------------------------------
  T* get() const;
  T& operator*() const;
  T* operator->() const;
  explicit operator bool() const;

  // Modifiers
  T* release();
  void reset(T* ptr = nullptr);
};

template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args);

}  // namespace tjs

#include "unique_ptr.tpp"

#endif  // TJS_UNIQUE_PTR_H
