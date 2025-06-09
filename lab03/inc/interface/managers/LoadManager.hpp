#pragma once

#include "interface/managers/SceneManager.hpp"
#include "ui/ObjectType.hpp"
#include <filesystem>
#include <objects/Object.hpp>

class LoadManager
{
  public:
    void loadScene(std::filesystem::path path, std::function<void(ObjectType, Object::id_type)> callback);

    void remove(Object::id_type id);

    void setSceneManager(std::shared_ptr<SceneManager> sceneManager);

  private:
    std::shared_ptr<SceneManager> sceneManager;
};
