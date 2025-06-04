#pragma once

#include "matrix/matrix/Matrix.hpp"
#include "visitors/ObjectVisitor.hpp"

class TransformVisitor : public ObjectVisitor {
	friend class Model;
public:
	TransformVisitor(const Matrix<double>& transform);

	void visit(Model &model) override;
	void visit(Camera &camera) override;
private:
	const Matrix<double>& transform;
};

