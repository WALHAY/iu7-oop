#pragma once

#include <objects/Object.hpp>
#include <wireframe/Wireframe.hpp>

class Model : public Object
{
    friend class DrawVisitor;
	friend class TransformVisitor;

  public:
    Model() : Object() {}
    Model(std::shared_ptr<Wireframe> wireframeModel);

    void accept(std::shared_ptr<ObjectVisitor> visitor) override;

  private:
    std::shared_ptr<Wireframe> wireframeModel;
};
