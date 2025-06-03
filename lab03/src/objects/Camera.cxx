#include <objects/Camera.hpp>

void Camera::accept(std::shared_ptr<ObjectVisitor> visitor)
{
	visitor->visit(*this);
}

