#ifndef TJS_FUNCTORS_H
#define TJS_FUNCTORS_H

namespace tjs {

template <typename T = void>
struct plus;

template <typename T = void>
struct minus;

template <typename T = void>
struct less;

template <typename T = void>
struct greater;

}  // namespace tjs

#include "functors.tpp"

#endif  // TJS_FUNCTORS_H
