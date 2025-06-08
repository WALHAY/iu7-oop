#pragma once

#include "objects/Model.hpp"
class WireframeModel : public Model
{
    friend class DrawVisitor;
    friend class TransformVisitor;

  public:
    WireframeModel(std::shared_ptr<Wireframe> wireframe);

	void accept(std::shared_ptr<ObjectVisitor> visitor) override;
  private:
    std::shared_ptr<Wireframe> wireframe;
};
