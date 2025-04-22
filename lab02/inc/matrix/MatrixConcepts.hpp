#pragma once

#include <concepts>

template <typename T>
concept Storable = std::semiregular<T>;

template <typename T, typename K>
concept AddableTo = requires(T a, K b){
	{a + b};
};

template <typename T, typename K>
concept AddableConvertible = requires(T a, K b){
	{a + b} -> std::convertible_to<T>;
};
