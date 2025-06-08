#pragma once

#include "loader/BaseDirector.hpp"

class ModelDirector : public BaseDirector
{
  public:
    ModelDirector(std::shared_ptr<BaseBuilder> builder);

    std::shared_ptr<Object> create(std::shared_ptr<BaseStreamReader> reader) override;

  protected:
    std::shared_ptr<BaseBuilder> builder;
};
