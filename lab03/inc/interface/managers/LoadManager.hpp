#pragma once

#include "interface/managers/SceneManager.hpp"
#include <filesystem>
#include <objects/Object.hpp>
#include <scene/loader/SceneDirector.hpp>

class LoadManager
{
  public:
    using id_type = Object::id_type;
	using callback_type = SceneDirector::callback_type;

    void loadScene(std::filesystem::path path, callback_type callback);

    void remove(std::shared_ptr<Scene> scene, Object::id_type id);

    void setSceneManager(std::shared_ptr<SceneManager> sceneManager);

  private:
    std::shared_ptr<SceneManager> sceneManager;
};
