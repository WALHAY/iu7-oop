#pragma once

#include <objects/Camera.hpp>
#include <objects/Model.hpp>

class ObjectVisitor
{
  public:
    virtual ~ObjectVisitor() = 0;

    virtual void visit(Model &model) = 0;
    virtual void visit(Camera &camera) = 0;
};

inline ObjectVisitor::~ObjectVisitor() = default;
