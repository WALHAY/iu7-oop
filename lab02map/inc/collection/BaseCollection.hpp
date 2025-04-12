#pragma once

#include <cstddef>

template<typename T>
class BaseCollection {

	public:
		BaseCollection();
		BaseCollection(const size_t initialSize);

		~BaseCollection() = 0;

		virtual void clear();

		virtual bool insert(T &&value);
		virtual bool insert(T &value);

		virtual bool remove(T &&value);
		virtual bool remove(T &value);

		virtual bool contains(T &&value) const;
		virtual bool contains(T &value) const;

		virtual bool isEmpty() const;

		virtual size_t getSize() const;

	private:
		size_t size;
};
