#pragma once

#include <concepts>

template<typename T>
concept EqualitiyComparable = std::equality_comparable<T>;
