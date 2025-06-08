#pragma once

#include <visitors/ObjectVisitor.hpp>

class ProjectionVisitor : public ObjectVisitor
{
    friend class PlainCamera;

  public:
    ProjectionVisitor(Point &p);

    void visit(WireframeModel &model) override;
    void visit(PlainCamera &camera) override;

  private:
    Point &point;
};
