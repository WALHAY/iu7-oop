#pragma once

#include "interface/managers/LoadManager.hpp"
#include <interface/managers/DrawManager.hpp>
#include <interface/managers/SceneManager.hpp>
#include <memory>

class BaseCommand
{
  public:
    virtual ~BaseCommand() = 0;
    virtual void execute() const = 0;

    void setManagers(std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<DrawManager> drawManager, std::shared_ptr<LoadManager> loadManager);

  protected:
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<DrawManager> drawManager;
    std::shared_ptr<LoadManager> loadManager;
};
