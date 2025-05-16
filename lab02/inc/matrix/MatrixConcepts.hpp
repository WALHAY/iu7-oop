#pragma once

#include <concepts>

template <typename T>
concept Storable = std::semiregular<T>;

template <typename T, typename K>
concept EqualityComparable = std::equality_comparable_with<T, K>;

template <typename T, typename K>
concept ConvertibleTo = std::convertible_to<T, K>;

template <typename T, typename K>
concept Addable = requires(T &a, K &b) {
    { a + b };
};

template <typename T, typename K>
concept AddableAssignable = requires(T &a, K &b) {
    { a + b } -> std::convertible_to<K>;
};

template <typename T, typename K>
concept Subtractable = requires(T &a, K &b) {
    { a - b };
};

template <typename T, typename K>
concept SubtractableAssignable = requires(T &a, K &b) {
    { a - b } -> std::convertible_to<K>;
};

template <typename T, typename K>
concept Multipliable = requires(T &a, K &b) {
    { a * b };
};

template <typename T, typename K>
concept MultipliableAssignable = requires(T &a, K &b) {
    { a * b } -> std::convertible_to<K>;
};

template <typename T, typename K>
concept Divisible = requires(T &a, K &b) {
    { a * b };
};

template <typename T, typename K>
concept DivisibleAssignable = requires(T &a, K &b) {
    { a * b } -> std::convertible_to<K>;
};

template <typename T>
concept LUComputable = requires(T &a, T &b) {
    { a - b } -> std::convertible_to<double>;
    { a * b } -> std::convertible_to<double>;
    { a / b } -> std::convertible_to<double>;
};

template <typename T>
concept DeterminantComputable = requires(T &a, T &b) {
    { a - b } -> std::convertible_to<double>;
    { a + b } -> std::convertible_to<double>;
    { a / b } -> std::convertible_to<double>;
    { a * b } -> std::convertible_to<double>;
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
concept Iterable = requires(T &a) {
    a.begin();
    a.end();
};

template <typename T>
concept InvertComputable = HasIdentityElement<T> && LUComputable<T>;
