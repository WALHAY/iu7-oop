#pragma once

#include "matrix/matrix/Matrix.hpp"
#include "visitors/ObjectVisitor.hpp"

class TransformVisitor : public ObjectVisitor
{
    friend class Model;
    friend class Camera;

  public:
    TransformVisitor(const Matrix<double> &transform);

    void visit(WireframeModel &model) override;
    void visit(PlainCamera &camera) override;

  private:
    const Matrix<double> &transform;
};
