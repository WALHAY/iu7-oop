#pragma once

#include <matrix/matrix/iterators/MatrixIteratorExceptions.hpp>
#include <matrix/matrix/iterators/ReverseMatrixIterator.hpp>

template <typename T>
ReverseMatrixIterator<T>::ReverseMatrixIterator(const Matrix<value_type> &matrix)
{
    this->it = iterator(matrix);
    this->matrixSize = matrix.getSize();
    this->currentIndex = matrixSize - 1;
}

template <typename T>
auto ReverseMatrixIterator<T>::operator*() const -> reference
{
    return this->it[currentIndex];
}

template <typename T>
auto ReverseMatrixIterator<T>::operator->() const -> pointer
{
    return this->it.operator->() + currentIndex;
}

template <typename T>
ReverseMatrixIterator<T> &ReverseMatrixIterator<T>::operator++()
{
    --currentIndex;
    return *this;
}

template <typename T>
ReverseMatrixIterator<T> ReverseMatrixIterator<T>::operator++(int) // postfix
{
    ReverseMatrixIterator<T> copy(*this);
    --currentIndex;
    return copy;
}
template <typename T>
ReverseMatrixIterator<T> ReverseMatrixIterator<T>::operator+(difference_type step) const
{
    ReverseMatrixIterator<T> newIter(*this);
    newIter.currentIndex -= step;
    return newIter;
}

template <typename T>
ReverseMatrixIterator<T> &ReverseMatrixIterator<T>::operator+=(difference_type step)
{
    currentIndex -= step;
    return *this;
}

template <typename T>
ReverseMatrixIterator<T> &ReverseMatrixIterator<T>::operator--()
{
    ++currentIndex;
    return *this;
}

template <typename T>
ReverseMatrixIterator<T> ReverseMatrixIterator<T>::operator--(int)
{
    ReverseMatrixIterator<T> copy(*this);
    ++currentIndex;
    return copy;
}

template <typename T>
ReverseMatrixIterator<T> ReverseMatrixIterator<T>::operator-(difference_type step) const
{
    ReverseMatrixIterator<T> newIter(*this);
    newIter->currentIndex += step;
    return newIter;
}

template <typename T>
ReverseMatrixIterator<T> &ReverseMatrixIterator<T>::operator-=(difference_type step)
{
    currentIndex += step;
    return *this;
}

template <typename T>
auto ReverseMatrixIterator<T>::operator-(const ReverseMatrixIterator<T> &iterator) const -> difference_type
{
    return this->currentIndex - iterator.currentIndex;
}

template <typename T>
auto ReverseMatrixIterator<T>::operator[](difference_type offset) const -> reference
{
    return *(*this + offset);
}

template <typename T>
bool ReverseMatrixIterator<T>::operator==(const ReverseMatrixIterator<T> &iterator) const noexcept
{
    return currentIndex == iterator.currentIndex && this->it == iterator.it;
}

template <typename T>
std::strong_ordering ReverseMatrixIterator<T>::operator<=>(const ReverseMatrixIterator &iterator) const noexcept
{
    return iterator <=> *this;
}

static_assert(std::random_access_iterator<ReverseMatrixIterator<const int>>,
              "ReverseMatrixIterator fails random access iterator concept");
