#pragma once

#include "objects/Object.hpp"
#include "wireframe/loader/BaseModelBuilder.hpp"
#include "wireframe/loader/BaseModelStreamReader.hpp"

class BaseModelDirector
{
  public:
    virtual ~BaseModelDirector() = 0;

    virtual std::shared_ptr<Object> create(std::shared_ptr<BaseModelStreamReader> reader) = 0;

  protected:
    std::shared_ptr<BaseModelBuilder> builder;
};

inline BaseModelDirector::~BaseModelDirector() = default;
