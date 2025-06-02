#include <interface/Facade.hpp>

Facade::Facade()
{
	sceneManager = std::make_shared<SceneManager>();
}

void Facade::execute(std::shared_ptr<Command> command)
{
	command->setManagers(sceneManager);
	command->execute();
}
