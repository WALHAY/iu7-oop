#pragma once

#include "wireframe/loader/BaseModelBuilder.hpp"
#include "wireframe/loader/BaseModelDirector.hpp"
#include "wireframe/loader/BaseModelStreamReader.hpp"

class ModelDirector : public BaseModelDirector
{
  public:
	ModelDirector() = delete;
    ModelDirector(std::shared_ptr<BaseModelBuilder> builder, std::shared_ptr<BaseModelStreamReader> reader);

    std::shared_ptr<Object> create() override;

  protected:
    std::shared_ptr<BaseModelBuilder> builder;
    std::shared_ptr<BaseModelStreamReader> reader;
};
