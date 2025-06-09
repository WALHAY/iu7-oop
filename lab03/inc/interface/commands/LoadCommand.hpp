#pragma once

#include "interface/commands/BaseCommand.hpp"
class LoadCommand : public BaseCommand
{
    using Action = void (LoadManager::*)(std::filesystem::path, std::function<void(ObjectType, Object::id_type)>);

  public:
    LoadCommand(std::filesystem::path path, std::function<void(ObjectType, Object::id_type)> callback)
        : path(path), callback(callback)
    {
    }

    void execute() const override
    {
        ((*loadManager).*action)(path, callback);
    }

  private:
    Action action = &LoadManager::loadScene;
    std::filesystem::path path;
    std::function<void(ObjectType, Object::id_type)> callback;
};
