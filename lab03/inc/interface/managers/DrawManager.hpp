#pragma once

#include "graphics/GraphicsFactory.hpp"
#include "graphics/QtGraphicsFactory.hpp"
#include <memory>
#include <interface/managers/SceneManager.hpp>
#include <QGraphicsScene>
	
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
