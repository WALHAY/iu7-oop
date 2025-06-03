#pragma once

#include <interface/commands/BaseCommand.hpp>
#include <interface/managers/DrawManager.hpp>

class DrawCommand : public BaseCommand
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
