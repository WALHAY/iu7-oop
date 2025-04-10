#include "base/BaseMatrixIterator.hpp"

template <typename T> bool BaseMatrixIterator<T>::operator==(const BaseMatrixIterator<T> &iter) const noexcept
{
    return iter.elementPtr.lock() == elementPtr.lock();
}

template <typename T> bool BaseMatrixIterator<T>::operator!=(const BaseMatrixIterator<T> &iter) const noexcept
{
    return iter.elementPtr.lock() != elementPtr.lock();
}

template <typename T> BaseMatrixIterator<T>::operator bool() const noexcept
{
    return isValid();
}

template <typename T> bool BaseMatrixIterator<T>::isValid()
{
    if (elementPtr == nullptr)
        return false;
    else if (elementPtr.expired())
        return false;
    return true;
}
