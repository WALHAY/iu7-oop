#pragma once

#include <objects/Object.hpp>

class Camera : public Object
{
  public:
	Camera() : Object() {}

    void accept(std::shared_ptr<ObjectVisitor> visitor) override;
};
