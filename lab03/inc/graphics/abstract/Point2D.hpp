#pragma once

class Point2D
{
  public:
    virtual ~Point2D() = 0;

	int x();
	int y();
};

inline Point2D::~Point2D() = default;
