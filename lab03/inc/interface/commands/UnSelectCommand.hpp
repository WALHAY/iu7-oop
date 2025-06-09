#pragma once

#include "interface/commands/BaseCommand.hpp"

class UnSelectCommand : public BaseCommand
{
    using Action = void (SelectionManager::*)(Object::id_type);

  public:
    UnSelectCommand(Object::id_type id) : id(id) {};

    void execute() const override
    {
        ((*selectionManager).*action)(id);
    }

  private:
    Action action = &SelectionManager::remove;

    Object::id_type id;
};
