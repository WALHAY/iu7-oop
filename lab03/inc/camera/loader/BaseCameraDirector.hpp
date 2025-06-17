#pragma once

#include "objects/Camera.hpp"
#include <memory>

class BaseCameraDirector
{
  public:
    virtual ~BaseCameraDirector() = 0;

    virtual std::shared_ptr<Camera> create() = 0;
};

inline BaseCameraDirector::~BaseCameraDirector() = default;
