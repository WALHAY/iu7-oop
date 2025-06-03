#pragma once

#include "matrix/matrix/Matrix.hpp"
#include "visitor/ObjectVisitor.hpp"

class TransformVisitor : public ObjectVisitor {
	friend class Model;
public:
	TransformVisitor(const Matrix<double>& transform);

	void visit(Model &model) override;
	void visit(Camera &camera) override;
private:
	const Matrix<double>& transform;
};

