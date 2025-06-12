#pragma once

#include "objects/Model.hpp"
#include <wireframe/BaseWireframe.hpp>

class WireframeModel : public Model
{
    friend class DrawVisitor;
    friend class TransformVisitor;

  public:
    WireframeModel(std::shared_ptr<BaseWireframe> wireframe);

    void accept(std::shared_ptr<ObjectVisitor> visitor) override;

  private:
    std::shared_ptr<BaseWireframe> wireframe;
};
