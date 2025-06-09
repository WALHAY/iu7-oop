#include <camera/CameraImpl.hpp>

static void decomposeTransform(const Matrix<double> &M, Matrix<double> &T, Matrix<double> &R)
{
    T = {{
        {1, 0, 0, M[0][3]},
        {0, 1, 0, M[1][3]},
        {0, 0, 1, M[2][3]},
        {M[3][0], M[3][1], M[3][2], 1}
    }};

    R = {{
        {M[0][0], M[0][1], M[0][2], 0},
        {M[1][0], M[1][1], M[1][2], 0},
        {M[2][0], M[2][1], M[2][2], 0},
        {0, 0, 0, 1}
    }};
}

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
	Matrix<double> translation(4, 4);
	Matrix<double> rotation(4, 4);

	decomposeTransform(matrix, translation, rotation);

    location.transform(translation);

    right.transform(rotation);
    up.transform(rotation);
    forward.transform(rotation);
}
