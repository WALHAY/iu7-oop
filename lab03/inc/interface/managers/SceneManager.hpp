#pragma once

#include <scene/Scene.hpp>

class SceneManager {
public:
	SceneManager();

	std::shared_ptr<Scene> getScene();
	void setScene(std::shared_ptr<Scene> scene);
private:
	std::shared_ptr<Scene> scene;
};


