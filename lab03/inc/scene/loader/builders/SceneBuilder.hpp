#pragma once

#include "camera/loader/BaseCameraDirector.hpp"
#include "scene/loader/BaseSceneBuilder.hpp"
class SceneBuilder : public BaseSceneBuilder
{
  public:
    SceneBuilder(std::shared_ptr<BaseModelDirector> director, std::shared_ptr<BaseCameraDirector> cameraDirector);

	void buildModel(std::filesystem::path &modelPath) override;
	void buildCamera(std::filesystem::path &cameraPath) override;

	std::shared_ptr<Scene> get() override;
  private:
    std::shared_ptr<BaseModelDirector> director;
    std::shared_ptr<BaseCameraDirector> cameraDirector;
};
