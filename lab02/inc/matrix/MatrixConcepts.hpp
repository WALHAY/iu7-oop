#pragma once

#include <concepts>

template <typename T>
concept Storable = std::semiregular<T>;

template <typename T, typename K>
concept ConvertibleTo = std::convertible_to<T, K> || std::same_as<T, K>;

template <typename T, typename K>
concept AddableTo = requires(T a, K b) {
    { a + b };
};

template <typename T, typename K>
concept AddableAssignable = requires(T a, K b) {
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

template <typename T>
concept DeterminantComputable = requires(T a, T b) {
    { a - b } -> std::convertible_to<double>;
    { a + b } -> std::convertible_to<double>;
    { a / b } -> std::convertible_to<double>;
};

template <typename T>
concept InvertComputable = requires  {
	{ true };
};

template <typename T>
concept HasZeroElement = requires {
    { T{0} };
};

template <typename T>
concept HasIdentityElement = requires {
    { T{1} };
};
