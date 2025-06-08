#include <visitors/TransformVisitor.hpp>

TransformVisitor::TransformVisitor(const Matrix<double> &transform) : transform(transform)
{
}

void TransformVisitor::visit(WireframeModel &model)
{
    model.wireframe->transform(transform);
}

void TransformVisitor::visit(PlainCamera &camera)
{
	camera.cameraImpl->transform(transform);
}
