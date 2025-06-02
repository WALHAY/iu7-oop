#pragma once

#include <interface/managers/SceneManager.hpp>

class Facade
{
  public:
    Facade();

  private:
	std::shared_ptr<SceneManager> sceneManager;
};
