#pragma once

#include <matrix/matrix/iterators/ConstMatrixIterator.hpp>
#include <matrix/matrix/iterators/MatrixIteratorExceptions.hpp>

template <typename T>
ConstMatrixIterator<T>::ConstMatrixIterator(const Matrix<value_type> &matrix)
{
    this->dataPtr = matrix.data;
    this->matrixSize = matrix.getSize();
    this->currentIndex = 0u;
}

template <typename T>
auto ConstMatrixIterator<T>::operator*() const -> reference
{
    validateIndex(currentIndex, __FILE_NAME__, __FUNCTION__, __LINE__);
    validatePointer(__FILE_NAME__, __FUNCTION__, __LINE__);

    return this->dataPtr.lock()[currentIndex];
}

template <typename T>
auto ConstMatrixIterator<T>::operator->() const -> pointer
{
    validateIndex(currentIndex, __FILE_NAME__, __FUNCTION__, __LINE__);
    validatePointer(__FILE_NAME__, __FUNCTION__, __LINE__);

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
    validateIndex(currentIndex + offset, __FILE_NAME__, __FUNCTION__, __LINE__);
    validatePointer(__FILE_NAME__, __FUNCTION__, __LINE__);

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
void ConstMatrixIterator<T>::validatePointer(const char *filename, const char *function, int line) const
{
    if (dataPtr.expired() || dataPtr.lock() == nullptr)
        throw IteratorExpiredException(filename, function, line, time(nullptr));
}

template <typename T>
void ConstMatrixIterator<T>::validateIndex(difference_type index, const char *filename, const char *function,
                                           int line) const
{
    if (index >= matrixSize || index < 0)
        throw IteratorInvalidIndexException(filename, function, line, time(nullptr));
}

static_assert(std::random_access_iterator<ConstMatrixIterator<const int>>,
              "ConstMatrixIterator fails random access iterator concept");
