#include <wireframe/Point.hpp>

Point::Point(double x, double y, double z) : x(x), y(y), z(z)
{
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

double Point::getZ() const
{
    return z;
}

void Point::setX(double x)
{
    this->x = x;
}
void Point::setY(double y)
{
    this->y = y;
}
void Point::setZ(double z)
{
    this->z = z;
}

void Point::transform(const Matrix<double> &matrix)
{
	Matrix<double> pointMatrix{{x, y, z, 1}};

	auto res = pointMatrix * matrix;

	x = res.at(0, 0);
	y = res.at(0, 1);
	z = res.at(0, 2);
}
