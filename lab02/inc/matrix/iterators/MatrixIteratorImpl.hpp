#pragma once

#include <matrix/iterators/MatrixIterator.hpp>
#include <matrix/iterators/MatrixIteratorExceptions.hpp>

template <typename T>
MatrixIterator<T>::MatrixIterator(const Matrix<value_type> &matrix)
{
    this->dataPtr = matrix.data;
    this->matrixSize = matrix.getSize();
    this->currentIndex = 0u;
}

template <typename T>
auto MatrixIterator<T>::operator*() const -> reference
{
    validateIndex(currentIndex, __FILE_NAME__, __FUNCTION__, __LINE__);
    validatePointer(__FILE_NAME__, __FUNCTION__, __LINE__);

    return this->dataPtr.lock()[currentIndex];
}

template <typename T>
auto MatrixIterator<T>::operator->() const -> pointer
{
    validateIndex(currentIndex, __FILE_NAME__, __FUNCTION__, __LINE__);
    validatePointer(__FILE_NAME__, __FUNCTION__, __LINE__);

    return this->dataPtr.lock().get() + currentIndex;
}

template <typename T>
MatrixIterator<T> &MatrixIterator<T>::operator++()
{
    ++currentIndex;
    return *this;
}

template <typename T>
MatrixIterator<T> MatrixIterator<T>::operator++(int) // postfix
{
    MatrixIterator<T> copy(*this);
    ++currentIndex;
    return copy;
}
template <typename T>
MatrixIterator<T> MatrixIterator<T>::operator+(difference_type step) const
{
    MatrixIterator<T> newIter(*this);
    newIter.currentIndex += step;
    return newIter;
}

template <typename T>
MatrixIterator<T> &MatrixIterator<T>::operator+=(difference_type step)
{
    currentIndex += step;
    return *this;
}

template <typename T>
MatrixIterator<T> &MatrixIterator<T>::operator--()
{
    --currentIndex;
    return *this;
}

template <typename T>
MatrixIterator<T> MatrixIterator<T>::operator--(int)
{
    MatrixIterator<T> copy(*this);
    --currentIndex;
    return copy;
}

template <typename T>
MatrixIterator<T> MatrixIterator<T>::operator-(difference_type step) const
{
    MatrixIterator<T> newIter(*this);
    newIter->currentIndex -= step;
    return newIter;
}

template <typename T>
MatrixIterator<T> &MatrixIterator<T>::operator-=(difference_type step)
{
    currentIndex -= step;
    return *this;
}

template <typename T>
auto MatrixIterator<T>::operator-(const MatrixIterator<T> &iterator) const -> difference_type
{
    return this->currentIndex - iterator.currentIndex;
}

template <typename T>
auto MatrixIterator<T>::operator[](difference_type offset) const -> reference
{
    validateIndex(currentIndex + offset, __FILE_NAME__, __FUNCTION__, __LINE__);
    validatePointer(__FILE_NAME__, __FUNCTION__, __LINE__);

    return *(*this + offset);
}

template <typename T>
bool MatrixIterator<T>::operator==(const MatrixIterator<T> &iterator) const noexcept
{
    return this->dataPtr.lock() == iterator.dataPtr.lock() && this->currentIndex == iterator.currentIndex;
}

template <typename T>
std::strong_ordering MatrixIterator<T>::operator<=>(const MatrixIterator &iterator) const noexcept
{
    if (auto cmp = dataPtr.lock() <=> iterator.dataPtr.lock(); cmp != 0)
    {
        return cmp;
    }

    return currentIndex <=> iterator.currentIndex;
}

template <typename T>
void MatrixIterator<T>::validatePointer(const char *filename, const char *function, int line) const
{
    if (dataPtr.expired() || dataPtr.lock() == nullptr)
        throw IteratorExpiredException(filename, function, line, time(nullptr));
}

template <typename T>
void MatrixIterator<T>::validateIndex(difference_type index, const char *filename, const char *function, int line) const
{
    if (index >= matrixSize || index < 0)
        throw IteratorInvalidIndexException(filename, function, line, time(nullptr));
}

static_assert(std::random_access_iterator<MatrixIterator<const int>>,
              "MatrixIterator fails random access iterator concept");
