#pragma once

#include "interface/managers/SceneManager.hpp"
#include <filesystem>
#include <objects/Object.hpp>

class LoadManager {
public:
	void loadScene(std::filesystem::path& path);

	void remove(Object::id_type id);

	void setSceneManager(std::shared_ptr<SceneManager> sceneManager);
private:
	std::shared_ptr<SceneManager> sceneManager;
};

