#pragma once

#include <objects/Camera.hpp>
#include <objects/Composite.hpp>

class ObjectVisitor
{
  public:
    virtual ~ObjectVisitor() = 0;

    virtual void visit(Composite &composite) = 0;
    virtual void visit(Camera &camera) = 0;
};

inline ObjectVisitor::~ObjectVisitor() = default;
