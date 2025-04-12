#pragma once

#include <memory>

template <typename T> class BaseIterator
{
  public:
    virtual ~BaseIterator() = 0;

    bool operator==(const BaseIterator<T> &iter) const noexcept override;
    bool operator!=(const BaseIterator<T> &iter) const noexcept override;

    operator bool() const noexcept;

    bool isValid();

  protected:
    std::weak_ptr<T> elementPtr;
};
