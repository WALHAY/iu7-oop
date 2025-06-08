#pragma once

#include <objects/Object.hpp>

class Camera : public Object
{
  public:
    virtual ~Camera();

    bool isCamera() override;
    void accept(std::shared_ptr<ObjectVisitor> visitor) override = 0;
};
