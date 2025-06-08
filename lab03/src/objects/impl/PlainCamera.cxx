#include <objects/impl/PlainCamera.hpp>
#include <visitors/ObjectVisitor.hpp>

PlainCamera::PlainCamera(std::shared_ptr<CameraImpl> impl) : cameraImpl(impl)
{
}

void PlainCamera::accept(std::shared_ptr<ObjectVisitor> visitor)
{
    visitor->visit(*this);
}
