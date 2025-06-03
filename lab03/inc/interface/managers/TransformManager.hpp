#pragma once

#include "interface/managers/SelectionManager.hpp"
#include "matrix/matrix/Matrix.hpp"

class TransformManager
{
  public:
    TransformManager() = default;

    void transform(const Matrix<double> &transform);

    void setSelectionManager(std::shared_ptr<SelectionManager> selectionManager);

  private:
    std::shared_ptr<SelectionManager> selectionManager;
};
