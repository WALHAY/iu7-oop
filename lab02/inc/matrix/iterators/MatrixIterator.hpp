#pragma once

#include "base/BaseMatrixIterator.hpp"
#include "matrix/MatrixConcepts.hpp"

template <Storable T>
class Matrix;

template <typename T>
class MatrixIterator : public BaseMatrixIterator
{
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_cv_t<T>;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::random_access_iterator_tag;

    friend class Matrix<value_type>;

    MatrixIterator() = default;
    explicit MatrixIterator(const Matrix<value_type> &matrix);
    MatrixIterator(const MatrixIterator &iterator) noexcept = default;
    MatrixIterator(MatrixIterator &&iterator) noexcept = default;

    MatrixIterator<T> &operator=(const MatrixIterator<T> &iterator) noexcept = default;
    MatrixIterator<T> &operator=(MatrixIterator<T> &&iterator) noexcept = default;

    reference operator*() const;
    pointer operator->() const;

    MatrixIterator<T> &operator++();
    MatrixIterator<T> operator++(int);
    MatrixIterator<T> operator+(difference_type) const;
    MatrixIterator<T> &operator+=(difference_type);

    friend MatrixIterator<T> operator+(difference_type offset, const MatrixIterator<T> &iterator)
    {
        return iterator + offset;
    }

    MatrixIterator<T> &operator--();
    MatrixIterator<T> operator--(int);
    MatrixIterator<T> operator-(difference_type) const;
    MatrixIterator<T> &operator-=(difference_type);

    difference_type operator-(const MatrixIterator<T> &iterator) const;

    reference operator[](difference_type) const;

    bool operator==(const MatrixIterator<T> &iterator) const noexcept;

    std::strong_ordering operator<=>(const MatrixIterator<T> &iterator) const noexcept;

  protected:
    void validateIndex(difference_type index, int line) const;
    void validatePointer(int line) const;

    std::weak_ptr<T[]> dataPtr;
};

#include <matrix/iterators/MatrixIteratorImpl.hpp>
