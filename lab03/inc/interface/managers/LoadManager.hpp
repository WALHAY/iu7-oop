#pragma once

#include "interface/managers/SceneManager.hpp"
#include "ui/ObjectType.hpp"
#include <filesystem>
#include <objects/Object.hpp>

class LoadManager
{
  public:
    void loadScene(std::filesystem::path &path);

    void remove(Object::id_type id);

    void setSceneManager(std::shared_ptr<SceneManager> sceneManager);

	void setLoadingCallback(std::function<void(ObjectType, Object::id_type)> callback);
  private:
    std::function<void(ObjectType, Object::id_type)> callback;
    std::shared_ptr<SceneManager> sceneManager;
};
