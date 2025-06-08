#pragma once

#include "camera/loader/BaseCameraDirector.hpp"
#include "scene/loader/BaseSceneBuilder.hpp"
#include <wireframe/loader/BaseModelDirector.hpp>

class SceneBuilder : public BaseSceneBuilder
{
  public:
    SceneBuilder(std::shared_ptr<BaseModelDirector> modelDirector, std::shared_ptr<BaseCameraDirector> cameraDirector);

	void build() override;

    void buildModel(std::filesystem::path &modelPath) override;
    void buildCamera(std::filesystem::path &cameraPath) override;

    std::shared_ptr<Scene> get() override;

  private:
    std::shared_ptr<BaseModelDirector> modelDirector;
    std::shared_ptr<BaseCameraDirector> cameraDirector;

	std::shared_ptr<Scene> scene;
};
