#include <interface/commands/Command.hpp>

Command::~Command() = default;

void Command::setManagers(std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<DrawManager> drawManager)
{
    this->sceneManager = sceneManager;
    this->drawManager = drawManager;
}
