#pragma once

#include "scene/loader/BaseSceneBuilder.hpp"
#include "scene/loader/BaseSceneStreamReader.hpp"
#include <memory>
class BaseSceneDirector
{
  public:
    BaseSceneDirector() = delete;
    BaseSceneDirector(std::shared_ptr<BaseSceneBuilder> builder);

	virtual ~BaseSceneDirector() = 0;

	virtual std::shared_ptr<Scene> create(std::shared_ptr<BaseSceneStreamReader> reader) = 0;
  private:
    std::shared_ptr<BaseSceneBuilder> builder;
};
