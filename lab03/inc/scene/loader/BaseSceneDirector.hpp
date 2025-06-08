#pragma once

#include "scene/loader/BaseSceneBuilder.hpp"
#include "scene/loader/BaseSceneStreamReader.hpp"
#include <memory>
class BaseSceneDirector
{
  public:
    virtual ~BaseSceneDirector() = 0;

    virtual std::shared_ptr<Scene> create(std::shared_ptr<BaseSceneStreamReader> reader) = 0;

  protected:
    std::shared_ptr<BaseSceneBuilder> builder;
};

inline BaseSceneDirector::~BaseSceneDirector() = default;
