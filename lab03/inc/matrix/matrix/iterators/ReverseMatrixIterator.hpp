#pragma once

#include "matrix/base/BaseMatrixIterator.hpp"
#include "matrix/matrix/MatrixConcepts.hpp"
#include "matrix/matrix/iterators/MatrixIterator.hpp"

template <Storable T>
class Matrix;

template <typename T>
class ReverseMatrixIterator : public BaseMatrixIterator
{
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_cv_t<T>;
    using pointer = T *;
    using reference = T &;
    using iterator = MatrixIterator<T>;
    using iterator_category = std::random_access_iterator_tag;

    friend class Matrix<value_type>;

    ReverseMatrixIterator() = default;
    explicit ReverseMatrixIterator(const Matrix<value_type> &matrix);
    ReverseMatrixIterator(const ReverseMatrixIterator &iterator) noexcept = default;
    ReverseMatrixIterator(ReverseMatrixIterator &&iterator) noexcept = default;

    ReverseMatrixIterator<T> &operator=(const ReverseMatrixIterator<T> &iterator) noexcept = default;
    ReverseMatrixIterator<T> &operator=(ReverseMatrixIterator<T> &&iterator) noexcept = default;

    reference operator*() const;
    pointer operator->() const;

    ReverseMatrixIterator<T> &operator++();
    ReverseMatrixIterator<T> operator++(int);
    ReverseMatrixIterator<T> operator+(difference_type) const;
    ReverseMatrixIterator<T> &operator+=(difference_type);

    friend ReverseMatrixIterator<T> operator+(difference_type offset, const ReverseMatrixIterator<T> &iterator)
    {
        return iterator + offset;
    }

    ReverseMatrixIterator<T> &operator--();
    ReverseMatrixIterator<T> operator--(int);
    ReverseMatrixIterator<T> operator-(difference_type) const;
    ReverseMatrixIterator<T> &operator-=(difference_type);

    difference_type operator-(const ReverseMatrixIterator<T> &iterator) const;

    reference operator[](difference_type) const;

    bool operator==(const ReverseMatrixIterator<T> &iterator) const noexcept;

    std::strong_ordering operator<=>(const ReverseMatrixIterator<T> &iterator) const noexcept;

  protected:
    iterator it;
};

#include <matrix/matrix/iterators/ReverseMatrixIteratorImpl.hpp>
