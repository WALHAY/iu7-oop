#pragma once

#include <concepts>

template <typename T>
concept Copyable = std::copyable<T>;

template <typename T>
concept Assignable = std::is_assignable_v<T, T>;

template <typename T>
concept Movable = std::is_move_assignable_v<T>;

template <typename T, typename U = T>
concept Addable = requires(T a, U b) {
    { a + b } -> std::common_with<T>;
    { a += b } -> std::same_as<T &>;
};

template <typename T, typename U = T>
concept Subtractable = requires(T a, U b) {
    { a - b } -> std::common_with<T>;
    { a -= b } -> std::same_as<T &>;
};

template <typename T, typename U = T>
concept Multipliable = requires(T a, U b) {
    { a *b } -> std::common_with<T>;
    { a *= b } -> std::same_as<T &>;
};

template <typename T>
concept Iterator = requires {
    typename T::value;
    typename T::ref;
    typename T::ptr;
    typename T::diff_type;
};
