#pragma once

#include "interface/commands/BaseCommand.hpp"
#include "interface/managers/TransformManager.hpp"
class TransformCommand : public BaseCommand
{
    using Action = void (TransformManager::*)(const Matrix<double> &);

  public:
    TransformCommand(const Matrix<double> &transform) : transform(transform) {};

    void execute() const override
    {
        ((*transformManager).*action)(transform);
    }

  private:
    Action action = &TransformManager::transform;
    const Matrix<double> &transform;
};
