#pragma once

#include <matrix/iterators/ConstMatrixIterator.hpp>
#include <matrix/iterators/MatrixIteratorExceptions.hpp>

template <typename T>
ConstMatrixIterator<T>::ConstMatrixIterator(const Matrix<value_type> &matrix)
{
    this->dataPtr = matrix.data;
    this->matrixSize = matrix.getSize();
    this->currentIndex = std::size_t{0};
}

template <typename T>
auto ConstMatrixIterator<T>::operator*() const -> reference
{
    validateIndex(currentIndex, __LINE__);
    validatePointer(__LINE__);

    return this->dataPtr.lock()[currentIndex];
}

template <typename T>
auto ConstMatrixIterator<T>::operator->() const -> pointer
{
    validateIndex(currentIndex, __LINE__);
    validatePointer(__LINE__);

    return this->dataPtr.lock().get() + currentIndex;
}

template <typename T>
ConstMatrixIterator<T> &ConstMatrixIterator<T>::operator++()
{
    ++currentIndex;
    return *this;
}

template <typename T>
ConstMatrixIterator<T> ConstMatrixIterator<T>::operator++(int) // postfix
{
    ConstMatrixIterator<T> copy(*this);
    ++currentIndex;
    return copy;
}
template <typename T>
ConstMatrixIterator<T> ConstMatrixIterator<T>::operator+(difference_type step) const
{
    ConstMatrixIterator<T> newIter(*this);
    newIter.currentIndex += step;
    return newIter;
}

template <typename T>
ConstMatrixIterator<T> &ConstMatrixIterator<T>::operator+=(difference_type step)
{
    currentIndex += step;
    return *this;
}

template <typename T>
ConstMatrixIterator<T> &ConstMatrixIterator<T>::operator--()
{
    --currentIndex;
    return *this;
}

template <typename T>
ConstMatrixIterator<T> ConstMatrixIterator<T>::operator--(int)
{
    ConstMatrixIterator<T> copy(*this);
    --currentIndex;
    return copy;
}

template <typename T>
ConstMatrixIterator<T> ConstMatrixIterator<T>::operator-(difference_type step) const
{
    ConstMatrixIterator<T> newIter(*this);
    newIter.currentIndex -= step;
    return newIter;
}

template <typename T>
ConstMatrixIterator<T> &ConstMatrixIterator<T>::operator-=(difference_type step)
{
    currentIndex -= step;
    return *this;
}

template <typename T>
auto ConstMatrixIterator<T>::operator-(const ConstMatrixIterator<T> &iterator) const -> difference_type
{
    return this->currentIndex - iterator.currentIndex;
}

template <typename T>
auto ConstMatrixIterator<T>::operator[](difference_type offset) const -> reference
{
    return *(*this + offset);
}

template <typename T>
bool ConstMatrixIterator<T>::operator==(const ConstMatrixIterator<T> &iterator) const noexcept
{
    return this->dataPtr.lock() == iterator.dataPtr.lock() && this->currentIndex == iterator.currentIndex;
}

template <typename T>
std::strong_ordering ConstMatrixIterator<T>::operator<=>(const ConstMatrixIterator &iterator) const noexcept
{
    if (auto cmp = dataPtr.lock() <=> iterator.dataPtr.lock(); cmp != 0)
    {
        return cmp;
    }

    return currentIndex <=> iterator.currentIndex;
}

template <typename T>
void ConstMatrixIterator<T>::validatePointer(int line) const
{
    if (dataPtr.expired() || dataPtr.lock() == nullptr)
        throw IteratorExpiredException(__FILE_NAME__, __FUNCTION__, line);
}

template <typename T>
void ConstMatrixIterator<T>::validateIndex(size_type index, int line) const
{
    if (index >= matrixSize)
        throw IteratorInvalidIndexException(__FILE_NAME__, __FUNCTION__, line);
}

static_assert(std::random_access_iterator<ConstMatrixIterator<const int>>,
              "ConstMatrixIterator fails random access iterator concept");
