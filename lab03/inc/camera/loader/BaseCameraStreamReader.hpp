#pragma once

#include "wireframe/Point.hpp"
#include <optional>

class BaseCameraStreamReader
{
  public:
	virtual ~BaseCameraStreamReader() = 0;

    virtual std::optional<Point> getLocation() = 0;
    virtual std::optional<Point> getDirection() = 0;
};

inline BaseCameraStreamReader::~BaseCameraStreamReader() = default;
