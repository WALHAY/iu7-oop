#pragma once

#include "wireframe/loader/BaseModelDirector.hpp"

class ModelDirector : public BaseModelDirector
{
  public:
	ModelDirector() = delete;
    ModelDirector(std::shared_ptr<BaseModelBuilder> builder);

    std::shared_ptr<Object> create(std::shared_ptr<BaseModelStreamReader> reader) override;

  protected:
    std::shared_ptr<BaseModelBuilder> builder;
};
