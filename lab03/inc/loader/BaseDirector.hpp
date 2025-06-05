#pragma once

#include "loader/BaseBuilder.hpp"
#include "loader/BaseStreamReader.hpp"
#include "objects/Object.hpp"

class BaseDirector
{
  public:
	BaseDirector() = delete;
    BaseDirector(std::shared_ptr<BaseBuilder> builder);
    virtual ~BaseDirector() = 0;

    virtual std::shared_ptr<Object> create(std::shared_ptr<BaseStreamReader> reader) = 0;

  protected:
    std::shared_ptr<BaseBuilder> builder;
};
