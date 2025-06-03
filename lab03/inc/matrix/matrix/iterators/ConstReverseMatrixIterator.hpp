#pragma once

#include "matrix/base/BaseMatrixIterator.hpp"
#include "matrix/matrix/MatrixConcepts.hpp"
#include "matrix/matrix/iterators/ConstMatrixIterator.hpp"

template <Storable T>
class Matrix;

template <typename T>
class ConstReverseMatrixIterator : public BaseMatrixIterator
{
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_cv_t<T>;
    using pointer = const T *;
    using reference = const T &;
    using iterator = ConstMatrixIterator<T>;
    using iterator_category = std::random_access_iterator_tag;

    friend class Matrix<value_type>;

    ConstReverseMatrixIterator() = default;
    explicit ConstReverseMatrixIterator(const Matrix<value_type> &matrix);
    ConstReverseMatrixIterator(const ConstReverseMatrixIterator &iterator) noexcept = default;
    ConstReverseMatrixIterator(ConstReverseMatrixIterator &&iterator) noexcept = default;

    ConstReverseMatrixIterator<T> &operator=(const ConstReverseMatrixIterator<T> &iterator) noexcept = default;
    ConstReverseMatrixIterator<T> &operator=(ConstReverseMatrixIterator<T> &&iterator) noexcept = default;

    reference operator*() const;
    pointer operator->() const;

    ConstReverseMatrixIterator<T> &operator++();
    ConstReverseMatrixIterator<T> operator++(int);
    ConstReverseMatrixIterator<T> operator+(difference_type) const;
    ConstReverseMatrixIterator<T> &operator+=(difference_type);

    friend ConstReverseMatrixIterator<T> operator+(difference_type offset,
                                                   const ConstReverseMatrixIterator<T> &iterator)
    {
        return iterator + offset;
    }

    ConstReverseMatrixIterator<T> &operator--();
    ConstReverseMatrixIterator<T> operator--(int);
    ConstReverseMatrixIterator<T> operator-(difference_type) const;
    ConstReverseMatrixIterator<T> &operator-=(difference_type);

    difference_type operator-(const ConstReverseMatrixIterator<T> &iterator) const;

    reference operator[](difference_type) const;

    bool operator==(const ConstReverseMatrixIterator<T> &iterator) const noexcept;

    std::strong_ordering operator<=>(const ConstReverseMatrixIterator<T> &iterator) const noexcept;

  protected:
    iterator it;
};

#include <matrix/matrix/iterators/ConstReverseMatrixIteratorImpl.hpp>
