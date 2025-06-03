#include <interface/commands/BaseCommand.hpp>

BaseCommand::~BaseCommand() = default;

void BaseCommand::setManagers(std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<DrawManager> drawManager)
{
    this->sceneManager = sceneManager;
    this->drawManager = drawManager;
}
