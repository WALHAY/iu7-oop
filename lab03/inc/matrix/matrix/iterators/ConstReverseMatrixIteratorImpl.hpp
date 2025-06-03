#pragma once

#include <matrix/matrix/iterators/ConstReverseMatrixIterator.hpp>
#include <matrix/matrix/iterators/MatrixIteratorExceptions.hpp>

template <typename T>
ConstReverseMatrixIterator<T>::ConstReverseMatrixIterator(const Matrix<value_type> &matrix)
{
    this->it = iterator(matrix);
    this->matrixSize = matrix.getSize();
    this->currentIndex = matrixSize - 1;
}

template <typename T>
auto ConstReverseMatrixIterator<T>::operator*() const -> reference
{
    return this->it[currentIndex];
}

template <typename T>
auto ConstReverseMatrixIterator<T>::operator->() const -> pointer
{
    return this->it.operator->() + currentIndex;
}

template <typename T>
ConstReverseMatrixIterator<T> &ConstReverseMatrixIterator<T>::operator++()
{
    --currentIndex;
    return *this;
}

template <typename T>
ConstReverseMatrixIterator<T> ConstReverseMatrixIterator<T>::operator++(int) // postfix
{
    ConstReverseMatrixIterator<T> copy(*this);
    --currentIndex;
    return copy;
}
template <typename T>
ConstReverseMatrixIterator<T> ConstReverseMatrixIterator<T>::operator+(difference_type step) const
{
    ConstReverseMatrixIterator<T> newIter(*this);
    newIter.currentIndex -= step;
    return newIter;
}

template <typename T>
ConstReverseMatrixIterator<T> &ConstReverseMatrixIterator<T>::operator+=(difference_type step)
{
    currentIndex -= step;
    return *this;
}

template <typename T>
ConstReverseMatrixIterator<T> &ConstReverseMatrixIterator<T>::operator--()
{
    ++currentIndex;
    return *this;
}

template <typename T>
ConstReverseMatrixIterator<T> ConstReverseMatrixIterator<T>::operator--(int)
{
    ConstReverseMatrixIterator<T> copy(*this);
    ++currentIndex;
    return copy;
}

template <typename T>
ConstReverseMatrixIterator<T> ConstReverseMatrixIterator<T>::operator-(difference_type step) const
{
    ConstReverseMatrixIterator<T> newIter(*this);
    newIter->currentIndex += step;
    return newIter;
}

template <typename T>
ConstReverseMatrixIterator<T> &ConstReverseMatrixIterator<T>::operator-=(difference_type step)
{
    currentIndex += step;
    return *this;
}

template <typename T>
auto ConstReverseMatrixIterator<T>::operator-(const ConstReverseMatrixIterator<T> &iterator) const -> difference_type
{
    return this->currentIndex - iterator.currentIndex;
}

template <typename T>
auto ConstReverseMatrixIterator<T>::operator[](difference_type offset) const -> reference
{
    return *(*this + offset);
}

template <typename T>
bool ConstReverseMatrixIterator<T>::operator==(const ConstReverseMatrixIterator<T> &iterator) const noexcept
{
    return currentIndex == iterator.currentIndex && this->it == iterator.it;
}

template <typename T>
std::strong_ordering ConstReverseMatrixIterator<T>::operator<=>(
    const ConstReverseMatrixIterator &iterator) const noexcept
{
    return iterator <=> *this;
}

static_assert(std::random_access_iterator<ConstReverseMatrixIterator<const int>>,
              "ConstReverseMatrixIterator fails random access iterator concept");
