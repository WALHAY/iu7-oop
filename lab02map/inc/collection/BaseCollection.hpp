#pragma once

#include <cstddef>

template<typename T>
class BaseCollection {

	public:
		BaseCollection();

		~BaseCollection() = 0;

		bool insert(T &&value);
		bool insert(T &value);

		bool contains(T &&value);
		bool contains(T &value);

		bool isEmpty();
		size_t getSize();

	private:
		size_t size;
};
