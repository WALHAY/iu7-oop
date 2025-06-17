#pragma once

#include "objects/Object.hpp"

class BaseModelDirector
{
  public:
    virtual ~BaseModelDirector() = 0;

    virtual std::shared_ptr<Object> create() = 0;
};

inline BaseModelDirector::~BaseModelDirector() = default;
