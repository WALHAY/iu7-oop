#pragma once

#include <iterator>
#include <type_traits>

template <typename T>
concept DefaultConstructible = std::is_default_constructible_v<T>;

template <typename T>
concept CopyConstructible = std::is_copy_constructible_v<T>;

template <typename T, typename K>
concept ConvertibleIterator = std::input_or_output_iterator<T> && std::convertible_to<std::iter_value_t<T>, K>;

