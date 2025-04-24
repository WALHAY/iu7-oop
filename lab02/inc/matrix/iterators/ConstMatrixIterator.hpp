#pragma once

#include "base/BaseMatrixIterator.hpp"
#include "matrix/MatrixConcepts.hpp"

template <Storable T>
class Matrix;

template <typename T>
class ConstMatrixIterator : public BaseMatrixIterator
{

  public:
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_cv_t<T>;
    using pointer = const T *;
    using reference = const T &;
    using iterator_category = std::random_access_iterator_tag;

    friend class Matrix<value_type>;

    ConstMatrixIterator() = default;
    explicit ConstMatrixIterator(const Matrix<value_type> &matrix);
    ConstMatrixIterator(const ConstMatrixIterator &iterator) noexcept = default;
    ConstMatrixIterator(ConstMatrixIterator &&iterator) noexcept = default;

    ConstMatrixIterator<T> &operator=(const ConstMatrixIterator<T> &iterator) noexcept = default;
    ConstMatrixIterator<T> &operator=(ConstMatrixIterator<T> &&iterator) noexcept = default;

    reference operator*() const;
    pointer operator->() const;

    ConstMatrixIterator<T> &operator++();
    ConstMatrixIterator<T> operator++(int);
    ConstMatrixIterator<T> operator+(difference_type) const;
    ConstMatrixIterator<T> &operator+=(difference_type);

    friend ConstMatrixIterator<T> operator+(difference_type offset, const ConstMatrixIterator<T> &iterator)
    {
        return iterator + offset;
    }

    ConstMatrixIterator<T> &operator--();
    ConstMatrixIterator<T> operator--(int);
    ConstMatrixIterator<T> operator-(difference_type) const;
    ConstMatrixIterator<T> &operator-=(difference_type);

    difference_type operator-(const ConstMatrixIterator<T> &iterator) const;

    reference operator[](difference_type) const;

    bool operator==(const ConstMatrixIterator<T> &iterator) const noexcept;

    std::strong_ordering operator<=>(const ConstMatrixIterator<T> &iterator) const noexcept;

  protected:
    void validateIndex(size_type index, int line) const;
    void validatePointer(int line) const;

    size_type matrixSize;
    size_type currentIndex;

    std::weak_ptr<T[]> dataPtr;
};

#include <matrix/iterators/ConstMatrixIteratorImpl.hpp>
