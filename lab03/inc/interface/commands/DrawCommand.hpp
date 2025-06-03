#pragma once

#include <interface/commands/Command.hpp>
#include <interface/managers/DrawManager.hpp>

class DrawCommand : public Command
{
  private:
    using Action = void (DrawManager::*)();

  public:
    void execute() const override
    {
        ((*drawManager).*action)();
    }

  private:
    Action action = &DrawManager::draw;
};
