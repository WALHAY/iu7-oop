#pragma once

#include "camera/loader/BaseCameraBuilder.hpp"
#include "camera/loader/BaseCameraStreamReader.hpp"
#include "objects/Camera.hpp"
#include "objects/Object.hpp"
#include <memory>

class BaseCameraDirector
{
  public:
	BaseCameraDirector() = delete;
    BaseCameraDirector(std::shared_ptr<BaseCameraBuilder> builder);

    virtual ~BaseCameraDirector() = 0;

    virtual std::shared_ptr<Camera> create(std::shared_ptr<BaseCameraStreamReader> reader);

  protected:
    std::shared_ptr<BaseCameraBuilder> builder;
};
