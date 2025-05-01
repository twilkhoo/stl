#include <utility>

namespace tjs {

// plus<T> primary template
template <typename T>
struct plus {
  constexpr T operator()(const T& lhs, const T& rhs) const { return lhs + rhs; }
};

// plus<void> specialization (transparent)
template <>
struct plus<void> {
  template <typename T1, typename T2>
  constexpr auto operator()(T1&& lhs, T2&& rhs) const
      -> decltype(std::forward<T1>(lhs) + std::forward<T2>(rhs)) {
    return std::forward<T1>(lhs) + std::forward<T2>(rhs);
  }
};

// minus<T> primary template
template <typename T>
struct minus {
  constexpr T operator()(const T& lhs, const T& rhs) const { return lhs - rhs; }
};

// minus<void> specialization (transparent)
template <>
struct minus<void> {
  template <typename T1, typename T2>
  constexpr auto operator()(T1&& lhs, T2&& rhs) const
      -> decltype(std::forward<T1>(lhs) - std::forward<T2>(rhs)) {
    return std::forward<T1>(lhs) - std::forward<T2>(rhs);
  }
};

// less<T> primary template
template <typename T>
struct less {
  constexpr bool operator()(const T& lhs, const T& rhs) const {
    return lhs < rhs;
  }
};

// less<void> specialization (transparent)
template <>
struct less<void> {
  template <typename T1, typename T2>
  constexpr auto operator()(T1&& lhs, T2&& rhs) const
      -> decltype(std::forward<T1>(lhs) < std::forward<T2>(rhs)) {
    return std::forward<T1>(lhs) < std::forward<T2>(rhs);
  }
};

// greater<T> primary template
template <typename T>
struct greater {
  constexpr bool operator()(const T& lhs, const T& rhs) const {
    return lhs > rhs;
  }
};

// greater<void> specialization (transparent)
template <>
struct greater<void> {
  template <typename T1, typename T2>
  constexpr auto operator()(T1&& lhs, T2&& rhs) const
      -> decltype(std::forward<T1>(lhs) > std::forward<T2>(rhs)) {
    return std::forward<T1>(lhs) > std::forward<T2>(rhs);
  }
};

}  // namespace tjs
