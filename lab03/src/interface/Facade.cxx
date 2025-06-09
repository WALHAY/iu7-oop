#include <QDebug>
#include <QGraphicsScene>
#include <interface/Facade.hpp>

Facade::Facade(std::shared_ptr<QGraphicsScene> graphicsScene, std::function<void(ObjectType, Object::id_type)> callback)
{
    sceneManager = std::make_shared<SceneManager>();
    drawManager = std::make_shared<DrawManager>(graphicsScene);
    selectionManager = std::make_shared<SelectionManager>();
    transformManager = std::make_shared<TransformManager>();
    loadManager = std::make_shared<LoadManager>();
    cameraManager = std::make_shared<CameraManager>();

    drawManager->setSceneManager(sceneManager);
    loadManager->setSceneManager(sceneManager);
    cameraManager->setSceneManager(sceneManager);

    transformManager->setSelectionManager(selectionManager);

    drawManager->setCameraManager(cameraManager);

	loadManager->setLoadingCallback(callback);

    std::filesystem::path p = "scene.txt";
    loadManager->loadScene(p);

	cameraManager->setActiveCamera(2);
}

void Facade::execute(std::shared_ptr<BaseCommand> command)
{
    command->setManagers(sceneManager, drawManager, loadManager, selectionManager, cameraManager);
    command->execute();
}
