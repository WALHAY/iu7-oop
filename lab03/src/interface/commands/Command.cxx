#include <interface/commands/Command.hpp>

Command::~Command() = default;

void Command::setManagers(std::shared_ptr<SceneManager> sceneManager)
{
    this->sceneManager = sceneManager;
}
