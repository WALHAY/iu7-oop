#pragma once

class Point {
public:
	Point(const Point &point) = default;
	Point(double x, double y, double z);

	double getX() const;
	double getY() const;
	double getZ() const;
	
	void setX(double x);
	void setY(double y);
	void setZ(double z);
private:
	double x;
	double y;
	double z;
};

