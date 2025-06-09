#pragma once

#include "interface/managers/SceneManager.hpp"
#include "objects/Composite.hpp"
#include <memory>
class SelectionManager
{
  public:
    using id_type = Object::id_type;
    SelectionManager();

    void add(std::shared_ptr<Scene> scene, id_type id);
    void remove(id_type id);

    std::shared_ptr<Composite> getSelection();

  private:
    std::shared_ptr<Composite> composite;
};
