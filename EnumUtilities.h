#pragma once
#include <type_traits>

template <typename E> constexpr auto toUnderlying(E e) noexcept {
  return static_cast<std::underlying_type_t<E>>(e);
}
