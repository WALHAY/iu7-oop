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

template <typename T, typename K>
concept HashFunction = std::is_invocable_v<T, K>;

template <typename T>
concept Movable = std::is_move_assignable_v<T> && std::is_move_constructible_v<T>;

template <typename T>
concept Copyable = std::is_copy_assignable_v<T> && std::is_copy_constructible_v<T>;

template<typename T>
concept MoveAndCopy = Movable<T> && Copyable<T>;
