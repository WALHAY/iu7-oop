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
concept Movable = std::is_move_assignable_v<T> && std::is_move_constructible_v<T>;

template <typename T>
concept Copyable = std::is_copy_assignable_v<T> && std::is_copy_constructible_v<T>;

template<typename T>
concept MoveAndCopy = Movable<T> && Copyable<T>;

template<typename C>
concept Container = requires(C c) {
    typename C::value_type;
    typename C::reference;
    typename C::const_reference;
    typename C::iterator;
    typename C::const_iterator;
    typename C::difference_type;
    typename C::size_type;
    
    { c.begin() } -> std::same_as<typename C::iterator>;
    { c.end() } -> std::same_as<typename C::iterator>;
    { c.size() } -> std::same_as<typename C::size_type>;
    { c.max_size() } -> std::same_as<typename C::size_type>;
    { c.empty() } -> std::same_as<bool>;
};
