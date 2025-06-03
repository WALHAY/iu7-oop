#pragma once

#include "graphics/GraphicsFactory.hpp"
#include "graphics/QtGraphicsFactory.hpp"
#include <QGraphicsScene>
#include <interface/managers/SceneManager.hpp>
#include <memory>

class DrawManager
{
  public:
    using GraphicsType = QtGraphicsFactory;
    DrawManager(std::shared_ptr<QGraphicsScene> scene);

    void draw();

    void setSceneManager(std::shared_ptr<SceneManager> sceneManager);

  private:
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<GraphicsFactory> graphicsFactory;
};
