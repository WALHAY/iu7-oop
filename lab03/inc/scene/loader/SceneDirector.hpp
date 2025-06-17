#pragma once

#include "camera/loader/BaseCameraDirector.hpp"
#include "scene/Scene.hpp"
#include "scene/loader/BaseSceneStreamReader.hpp"
#include "wireframe/loader/BaseModelDirector.hpp"
#include <memory>
#include <objects/Object.hpp>

class SceneDirector
{
  public:
	using callback_type = std::function<void(ObjectType, Object::id_type)>;
    SceneDirector(std::shared_ptr<BaseModelDirector> modelDirector, std::shared_ptr<BaseCameraDirector> cameraDirector,
                  std::shared_ptr<BaseSceneStreamReader> sceneReader);

    std::shared_ptr<Scene> create();

	void setCallback(callback_type callback);

  private:
	callback_type callback;

    std::shared_ptr<BaseModelDirector> modelDirector;
    std::shared_ptr<BaseCameraDirector> cameraDirector;

    std::shared_ptr<BaseSceneStreamReader> sceneReader;
};
