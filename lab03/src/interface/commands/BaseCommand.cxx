#include <interface/commands/BaseCommand.hpp>

BaseCommand::~BaseCommand() = default;

void BaseCommand::setManagers(std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<DrawManager> drawManager,
                              std::shared_ptr<LoadManager> loadManager)
{
    this->sceneManager = sceneManager;
    this->drawManager = drawManager;
    this->loadManager = loadManager;
}
