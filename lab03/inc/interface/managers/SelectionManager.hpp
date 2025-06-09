#pragma once

#include "interface/managers/SceneManager.hpp"
#include "objects/Composite.hpp"
#include <memory>
class SelectionManager
{
  public:
    using id_type = Object::id_type;
    SelectionManager();

    void setSceneManager(std::shared_ptr<SceneManager> sceneManager);

    void add(id_type id);
    void remove(id_type id);

    std::shared_ptr<Composite> getSelection();

  private:
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<Composite> composite;
};
