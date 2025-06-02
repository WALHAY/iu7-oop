#pragma once

#include <memory>
#include <interface/managers/SceneManager.hpp>

class Command
{
  public:
    virtual ~Command() = 0;
    virtual void execute() = 0;

    void setManagers(std::shared_ptr<SceneManager> sceneManager);

  private:
	std::shared_ptr<SceneManager> sceneManager;
};
