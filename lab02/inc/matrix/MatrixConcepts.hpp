#pragma once

#include <concepts>

template <typename T>
concept Storable = std::semiregular<T>;

template <typename T, typename K>
concept ConvertibleTo = std::convertible_to<T, K> || std::same_as<T, K>;

template <typename T, typename K>
concept AddableTo = requires(T a, K b) {
	{a + b};
};

template <typename T, typename K>
concept AddableConvertible = requires(T a, K b) {
    { a + b } -> std::convertible_to<T>;
};

template <typename T, typename K>
concept SubtractableTo = requires(T a, K b) {
    { a - b };
};

template <typename T, typename K>
concept SubtractableConvertible = requires(T a, K b) {
    { a - b } -> std::convertible_to<T>;
};
