#pragma once

#include "interface/commands/BaseCommand.hpp"

class RemoveCameraCommand : public BaseCommand
{
    using Action = void (CameraManager::*)();

  public:
    RemoveCameraCommand()
    {
    }

    void execute() const override
    {
        ((*cameraManager).*action)();
    }

  private:
    Action action = &CameraManager::removeActiveCamera;
};
