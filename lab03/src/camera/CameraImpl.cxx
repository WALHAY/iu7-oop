#include <camera/CameraImpl.hpp>

CameraImpl::CameraImpl(const Point &location) : location(location)
{
}

Point CameraImpl::getLocation()
{
    return location;
}

void CameraImpl::setLocation(const Point &location)
{
    this->location = location;
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

void CameraImpl::setForward(const Point &forward)
{
    this->forward = forward;
}

void CameraImpl::setUp(const Point &up)
{
    this->up = up;
}

void CameraImpl::setRight(const Point &right)
{
    this->right = right;
}

void CameraImpl::transform(const Matrix<double> &matrix)
{
    location.transform(matrix);

    right.transform(matrix);
    up.transform(matrix);
    forward.transform(matrix);
}
