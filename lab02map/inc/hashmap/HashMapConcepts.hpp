#pragma once

#include <concepts>
#include <iterator>

template <typename T>
concept EqualityComparable = std::equality_comparable<T>;

template <typename T, typename K>
concept HashFunction = std::is_invocable_v<T, K> && requires(T a, K b) {
    { a(b) } -> std::convertible_to<std::size_t>;
};

template <typename T, typename K>
concept EqualFunction = std::is_invocable_v<T, K, K> && requires(T a, const K& b, const K& c) {
	{ a(b, c) } -> std::same_as<bool>;
};

template <typename T>
concept Movable = std::is_move_assignable_v<T> && std::is_move_constructible_v<T>;

template <typename T>
concept Copyable = std::is_copy_assignable_v<T> && std::is_copy_constructible_v<T>;

template <typename T>
concept MoveAndCopy = Movable<T> && Copyable<T>;
