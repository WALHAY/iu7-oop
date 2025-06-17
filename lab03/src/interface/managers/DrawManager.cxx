#include "interface/managers/CameraManager.hpp"
#include "interface/managers/ManagersExceptions.hpp"
#include "ui/RenderConfig.hpp"
#include <interface/managers/DrawManager.hpp>
#include <visitors/DrawVisitor.hpp>

DrawManager::DrawManager(std::shared_ptr<QGraphicsScene> scene)
{
    graphicsFactory = std::make_shared<GraphicsType>(scene);
}

void DrawManager::draw()
{
    if (sceneManager == nullptr)
        throw SceneManagerNotSetException(__FILE_NAME__, __FUNCTION__, __LINE__);

    if (cameraManager->getActiveCamera() == nullptr)
        throw NoCameraSetException(__FILE_NAME__, __FUNCTION__, __LINE__);

    auto canvas = graphicsFactory->createCanvas(RenderWidth, RenderHeight);

    std::shared_ptr<DrawVisitor> drawVisitor =
        std::make_shared<DrawVisitor>(graphicsFactory, canvas, cameraManager->getActiveCamera());

    auto scene = sceneManager->getScene();
	if(!scene)
		return;

    for (const auto &obj : *scene)
        obj->accept(drawVisitor);

    auto graphics = graphicsFactory->getGraphics();
    graphics->displayCanvas(canvas);
}

void DrawManager::setSceneManager(std::shared_ptr<SceneManager> sceneManager)
{
    this->sceneManager = sceneManager;
}

void DrawManager::setCameraManager(std::shared_ptr<CameraManager> cameraManager)
{
    this->cameraManager = cameraManager;
}
