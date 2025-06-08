#pragma once

#include "scene/loader/BaseSceneDirector.hpp"

class SceneDirector : public BaseSceneDirector
{
  public:
    SceneDirector(std::shared_ptr<BaseSceneBuilder> builder);

    std::shared_ptr<Scene> create(std::shared_ptr<BaseSceneStreamReader> reader) override;
};
