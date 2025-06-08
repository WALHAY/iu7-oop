#pragma once

#include "objects/Object.hpp"
#include "wireframe/loader/BaseBuilder.hpp"
#include "wireframe/loader/BaseStreamReader.hpp"

class BaseDirector
{
  public:
    BaseDirector(std::shared_ptr<BaseBuilder> builder);
    virtual ~BaseDirector() = 0;

    virtual std::shared_ptr<Object> create(std::shared_ptr<BaseStreamReader> reader) = 0;

  protected:
    std::shared_ptr<BaseBuilder> builder;
};
