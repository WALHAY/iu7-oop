#pragma once

#include <objects/Object.hpp>

class Camera : public Object
{
  public:
	Camera() = default;

    void accept(std::shared_ptr<ObjectVisitor> visitor) override;
};
