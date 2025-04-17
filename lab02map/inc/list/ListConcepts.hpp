#pragma once

#include <type_traits>
#include <iterator>

template <typename T>
concept DefaultConstructible = requires
{
	T();
};

template <typename T>
concept CopyConstructible = std::is_copy_constructible_v<T>;

template <typename T>
concept Iterator = std::input_or_output_iterator<T>; 
