#pragma once

#include <objects/Object.hpp>
#include <wireframe/Wireframe.hpp>

class Model : public Object
{
    friend class DrawVisitor;

  public:
    Model() = default;
    Model(std::shared_ptr<Wireframe> wireframeModel);

    void accept(std::shared_ptr<ObjectVisitor> visitor) override;

  private:
    std::shared_ptr<Wireframe> wireframeModel;
};
