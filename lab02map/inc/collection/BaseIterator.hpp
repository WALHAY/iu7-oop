#pragma once

#include <memory>

template <typename T> class BaseMatrixIterator
{
  public:
    virtual ~BaseMatrixIterator() = 0;

    bool operator==(const BaseMatrixIterator<T> &iter) const noexcept override;
    bool operator!=(const BaseMatrixIterator<T> &iter) const noexcept override;

    operator bool() const noexcept;

    bool isValid();

  protected:
    std::weak_ptr<T> elementPtr;
};
