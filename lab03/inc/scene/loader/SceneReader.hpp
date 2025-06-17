#pragma once

#include "scene/loader/BaseSceneStreamReader.hpp"
#include "ui/ObjectType.hpp"
#include <memory>

class SceneReader : public BaseSceneStreamReader
{
  public:
    SceneReader(std::shared_ptr<std::istream> stream);

    std::optional<ObjectType> getType() override;

  private:
    std::shared_ptr<std::istream> stream;
};
