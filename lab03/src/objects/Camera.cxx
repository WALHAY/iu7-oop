#include <objects/Camera.hpp>
#include <visitors/ObjectVisitor.hpp>



void Camera::accept(std::shared_ptr<ObjectVisitor> visitor)
{
    visitor->visit(*this);
}
