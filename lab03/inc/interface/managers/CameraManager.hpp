#pragma once

#include "interface/managers/SceneManager.hpp"
#include "objects/Camera.hpp"
#include <memory>
class CameraManager
{
  public:
    void setActiveCamera(Object::id_type id);
	std::shared_ptr<Camera> getActiveCamera();

	void setSceneManager(std::shared_ptr<SceneManager> sceneManager);

  private:
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<Camera> activeCamera;
};
