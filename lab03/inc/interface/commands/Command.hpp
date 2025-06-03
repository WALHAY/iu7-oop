#pragma once

#include <interface/managers/DrawManager.hpp>
#include <interface/managers/SceneManager.hpp>
#include <memory>

class Command
{
  public:
    virtual ~Command() = 0;
    virtual void execute() const = 0;

    void setManagers(std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<DrawManager> drawManager);

  protected:
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<DrawManager> drawManager;
};
