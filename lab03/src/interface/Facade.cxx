#include <interface/Facade.hpp>
#include <QGraphicsScene>

Facade::Facade(std::shared_ptr<QGraphicsScene> graphicsScene)
{
	sceneManager = std::make_shared<SceneManager>();
	drawManager = std::make_shared<DrawManager>(graphicsScene);

	drawManager->setSceneManager(sceneManager);

	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	sceneManager->setScene(scene);
}

void Facade::execute(std::shared_ptr<Command> command)
{
	command->setManagers(sceneManager, drawManager);
	command->execute();
}
