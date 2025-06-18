#pragma once

#include "objects/Camera.hpp"
#include "scene/Scene.hpp"
#include <memory>

class CameraManager
{
  public:
    void setActiveCamera(std::shared_ptr<Scene> scene, Object::id_type id);
	std::shared_ptr<Camera> getActiveCamera();
	void removeActiveCamera();

  private:
    std::shared_ptr<Camera> activeCamera;
};
