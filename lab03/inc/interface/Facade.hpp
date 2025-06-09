#pragma once

#include "interface/managers/CameraManager.hpp"
#include "interface/managers/LoadManager.hpp"
#include "interface/managers/TransformManager.hpp"
#include <interface/commands/BaseCommand.hpp>
#include <interface/managers/SceneManager.hpp>

class Facade
{
  public:
    Facade(std::shared_ptr<QGraphicsScene> graphicsScene, std::function<void(ObjectType, Object::id_type)> callback);

    void execute(std::shared_ptr<BaseCommand> command);

  private:
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<DrawManager> drawManager;
    std::shared_ptr<SelectionManager> selectionManager;
    std::shared_ptr<TransformManager> transformManager;
    std::shared_ptr<LoadManager> loadManager;
    std::shared_ptr<CameraManager> cameraManager;
};
