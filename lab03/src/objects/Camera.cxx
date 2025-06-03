#include <objects/Camera.hpp>
#include <visitor/ObjectVisitor.hpp>



void Camera::accept(std::shared_ptr<ObjectVisitor> visitor)
{
    visitor->visit(*this);
}
