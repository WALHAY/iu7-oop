#pragma once

#include <concepts>

template <typename T>
concept Storable = std::semiregular<T>;

template <typename T, typename K>
concept ConvertibleTo = std::convertible_to<T, K>;

template <typename T, typename K>
concept AddableTo = requires(T a, K b) {
    { a + b };
};

template <typename T, typename K>
concept AddableAssignable = requires(T a, K b) {
    { a + b } -> std::convertible_to<K>;
};

template <typename T, typename K>
concept SubtractableTo = requires(T a, K b) {
    { a - b };
};

template <typename T, typename K>
concept SubtractableAssignable = requires(T a, K b) {
    { a - b } -> std::convertible_to<K>;
};

template <typename T, typename K>
concept MultipliableTo = requires(T a, K b) {
    { a * b };
};

template <typename T, typename K>
concept MultipliableAssignable = requires(T a, K b) {
    { a * b } -> std::convertible_to<K>;
};

template <typename T>
concept LUComputable = requires(T a, T b) {
    { a - b } -> std::convertible_to<double>;
    { a * b } -> std::convertible_to<double>;
    { a / b } -> std::convertible_to<double>;
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

template <typename T>
concept Container = requires(T &a) {
	a.begin();
	a.end();
};
