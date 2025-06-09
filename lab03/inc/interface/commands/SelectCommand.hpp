#pragma once

#include "interface/commands/BaseCommand.hpp"

class SelectCommand : public BaseCommand
{
    using Action = void (SelectionManager::*)(Object::id_type);

  public:
    SelectCommand(Object::id_type id) : id(id) {};

    void execute() const override
    {
        ((*selectionManager).*action)(id);
    }

  private:
    Action action = &SelectionManager::add;

    Object::id_type id;
};
