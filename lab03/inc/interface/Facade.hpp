#pragma once

#include <interface/commands/Command.hpp>
#include <interface/managers/SceneManager.hpp>

class Facade
{
  public:
    Facade();

    void execute(std::shared_ptr<Command> command);

  private:
    std::shared_ptr<SceneManager> sceneManager;
};
