#pragma once

#include <concepts>

template <typename T>
concept Storable = std::semiregular<T>;
