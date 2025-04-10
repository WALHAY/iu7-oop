#pragma once

#include <concepts>

template<typename T>
concept Copyable = requires(T a) {T(a);};

template<typename T>
concept Assignable = requires(T a, T b) { b = a; };

template<typename T>
concept Movable = requires(T &&a) { T(a); };

template<typename T, typename U>
concept Addable = requires(T a, U b) { a + b; };

template<typename T, typename U>
concept Subtractable = requires(T a, U b) { a - b; };

template<typename T, typename U>
concept Multipliable = requires(T a, U b) { a * b; };
