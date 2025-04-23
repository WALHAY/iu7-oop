#pragma once

#include <cstddef>
#include <utility>

class BaseMatrix
{
  public:
	using size_type = std::pair<std::size_t, std::size_t>;

    virtual ~BaseMatrix() = 0;

    bool isEmpty() const;

	size_type getSize() const {
		return size;
	}

	size_t getElements() const {
		return size.first * size.second;
	}

  protected:
	size_type size;
};
