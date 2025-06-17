#include <QDebug>
#include <QGraphicsScene>
#include <interface/Facade.hpp>

Facade::Facade(std::shared_ptr<QGraphicsScene> graphicsScene)
{
    sceneManager = std::make_shared<SceneManager>();
    drawManager = std::make_shared<DrawManager>(graphicsScene);
    selectionManager = std::make_shared<SelectionManager>();
    transformManager = std::make_shared<TransformManager>();
    loadManager = std::make_shared<LoadManager>();
    cameraManager = std::make_shared<CameraManager>();

    drawManager->setSceneManager(sceneManager);
    loadManager->setSceneManager(sceneManager);

    transformManager->setSelectionManager(selectionManager);

    drawManager->setCameraManager(cameraManager);
}

void Facade::execute(std::shared_ptr<BaseCommand> command)
{
    command->setManagers(sceneManager, drawManager, loadManager, selectionManager, cameraManager, transformManager);
    command->execute();
}
