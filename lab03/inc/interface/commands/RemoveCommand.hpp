#pragma once

#include <interface/commands/BaseCommand.hpp>
#include <interface/managers/LoadManager.hpp>

class RemoveCommand : public BaseCommand
{
  private:
    using Action = void (LoadManager::*)(std::shared_ptr<Scene>, Object::id_type);

  public:
    RemoveCommand(Object::id_type id) : id(id)
    {
    }

    void execute() const override
    {
        ((*loadManager).*action)(sceneManager->getScene(), id);
    }

  private:
    Object::id_type id;
    Action action = &LoadManager::remove;
};
