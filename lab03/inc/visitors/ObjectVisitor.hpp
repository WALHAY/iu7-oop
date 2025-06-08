#pragma once

#include "objects/impl/PlainCamera.hpp"
#include "objects/impl/WireframeModel.hpp"
#include <objects/Camera.hpp>
#include <objects/Model.hpp>

class ObjectVisitor
{
  public:
    virtual ~ObjectVisitor() = 0;

    virtual void visit(WireframeModel &model) = 0;
    virtual void visit(PlainCamera &camera) = 0;
};

inline ObjectVisitor::~ObjectVisitor() = default;
