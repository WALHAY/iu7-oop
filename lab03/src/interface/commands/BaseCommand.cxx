#include <interface/commands/BaseCommand.hpp>

BaseCommand::~BaseCommand() = default;

void BaseCommand::setManagers(std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<DrawManager> drawManager,
                              std::shared_ptr<LoadManager> loadManager,
                              std::shared_ptr<SelectionManager> selectionManager,
                              std::shared_ptr<CameraManager> cameraManager)
{
    this->sceneManager = sceneManager;
    this->drawManager = drawManager;
    this->loadManager = loadManager;
    this->selectionManager = selectionManager;
    this->cameraManager = cameraManager;
}
