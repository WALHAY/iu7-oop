#pragma once

#include <concepts>

template <typename T>
concept EqualityComparable = std::equality_comparable<T>;

template <typename T, typename K>
concept HashFunction = requires(T a, const K& b) {
	requires std::is_nothrow_invocable_v<T, const K&>;
    { a(b) } -> std::convertible_to<std::size_t>;
};

template <typename T, typename K>
concept EqualFunction = requires (T a, const K &b, const K &c) { 
	requires std::is_invocable_v<T, const K&, const K&>;
	{ a(b, c) } -> std::same_as<bool>;
};

template <typename T>
concept Movable = std::is_move_assignable_v<T> && std::is_move_constructible_v<T>;

template <typename T>
concept Copyable = std::is_copy_assignable_v<T> && std::is_copy_constructible_v<T>;

template <typename T>
concept MoveAndCopy = Movable<T> && Copyable<T>;
