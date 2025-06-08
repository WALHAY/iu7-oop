#pragma once

#include "camera/loader/BaseCameraBuilder.hpp"
#include "camera/loader/BaseCameraStreamReader.hpp"
#include "objects/Camera.hpp"
#include <memory>

class BaseCameraDirector
{
  public:
    virtual ~BaseCameraDirector() = 0;

    virtual std::shared_ptr<Camera> create(std::shared_ptr<BaseCameraStreamReader> reader) = 0;

  protected:
    std::shared_ptr<BaseCameraBuilder> builder;
};

inline BaseCameraDirector::~BaseCameraDirector() = default;
