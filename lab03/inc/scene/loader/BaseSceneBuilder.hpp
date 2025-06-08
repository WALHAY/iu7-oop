#pragma once

#include "scene/Scene.hpp"
#include "wireframe/loader/BaseModelDirector.hpp"
#include <filesystem>
#include <memory>
class BaseSceneBuilder
{
  public:
    virtual ~BaseSceneBuilder() = 0;

    virtual void build() = 0;

    virtual void buildModel(std::filesystem::path &modelPath) = 0;
	virtual void buildCamera(std::filesystem::path &cameraPath) = 0;

    virtual std::shared_ptr<Scene> get() = 0;
};
