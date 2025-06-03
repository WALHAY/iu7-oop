#include <interface/managers/DrawManager.hpp>
#include <visitor/DrawVisitor.hpp>

DrawManager::DrawManager(std::shared_ptr<QGraphicsScene> scene)
{
    graphicsFactory = std::make_shared<GraphicsType>(scene);
}

void DrawManager::draw()
{
    if (sceneManager == nullptr)
    {
        return;
    }

    auto canvas = graphicsFactory->createCanvas(1280, 720);

    std::shared_ptr<DrawVisitor> drawVisitor =
        std::make_shared<DrawVisitor>(graphicsFactory, canvas, std::make_shared<Camera>());

    auto scene = sceneManager->getScene();
    for (const auto &obj : *scene)
    {
        obj->accept(drawVisitor);
    }

    auto graphics = graphicsFactory->getGraphics();
    graphics->displayCanvas(canvas);
}

void DrawManager::setSceneManager(std::shared_ptr<SceneManager> sceneManager)
{
    this->sceneManager = sceneManager;
}
