#pragma once

#include <istream>
#include <memory>

class BaseStreamLoader
{
  public:
    virtual ~BaseStreamLoader() = 0;

    virtual std::shared_ptr<std::istream> getStream() = 0;
    virtual void closeStream() = 0;

  protected:
    std::shared_ptr<std::istream> stream;
};

inline BaseStreamLoader::~BaseStreamLoader() = default;
