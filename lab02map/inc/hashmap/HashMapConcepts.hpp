#pragma once

#include <concepts>
#include <functional>

template <typename T>
concept EqualitiyComparable = std::equality_comparable<T>;

template <typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<size_t>;
};

template <typename T>
concept HashAndEqual = EqualitiyComparable<T> && Hashable<T>;

template <typename T>
concept Movable = std::movable<T>;

template <typename T>
concept Copyable = std::copyable<T>;

template<typename T>
concept MoveAndCopy = Movable<T> && Copyable<T>;
