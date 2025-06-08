#include <interface/managers/DrawManager.hpp>
#include <visitors/DrawVisitor.hpp>

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

    auto cI = std::make_shared<CameraImpl>(Point(0, 0, 0));
    std::shared_ptr<DrawVisitor> drawVisitor =
        std::make_shared<DrawVisitor>(graphicsFactory, canvas, std::make_shared<PlainCamera>(cI));

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
