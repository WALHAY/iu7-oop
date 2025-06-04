#include <visitors/TransformVisitor.hpp>

TransformVisitor::TransformVisitor(const Matrix<double> &transform) : transform(transform)
{
}

void TransformVisitor::visit(Model &model)
{
    model.wireframeModel->transform(transform);
}

void TransformVisitor::visit(Camera &camera)
{
}
