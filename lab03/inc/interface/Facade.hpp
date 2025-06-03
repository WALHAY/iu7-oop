#pragma once

#include <interface/commands/Command.hpp>
#include <interface/managers/SceneManager.hpp>

class Facade
{
  public:
    Facade(std::shared_ptr<QGraphicsScene> graphicsScene);

    void execute(std::shared_ptr<Command> command);

  private:
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<DrawManager> drawManager;
};
