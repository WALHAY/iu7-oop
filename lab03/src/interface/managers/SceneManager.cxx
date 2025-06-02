#include <interface/managers/SceneManager.hpp>

SceneManager::SceneManager() {

}

void SceneManager::setScene(std::shared_ptr<Scene> scene)
{
	this->scene = scene;
}

std::shared_ptr<Scene> SceneManager::getScene() {
	return scene;
}
