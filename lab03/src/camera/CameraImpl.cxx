#include <camera/CameraImpl.hpp>

CameraImpl::CameraImpl(Point location) : location(location)
{
}

Point CameraImpl::getForward()
{
    return forward;
}

Point CameraImpl::getUp()
{
    return up;
}

Point CameraImpl::getRight()
{
    return right;
}

Point CameraImpl::getLocation()
{
    return location;
}
