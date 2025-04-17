#pragma once

#include <type_traits>

template <typename T>
concept DefaultConstructible = requires
{
	T();
};

template <typename T>
concept CopyConstructible = std::is_copy_constructible_v<T>;
