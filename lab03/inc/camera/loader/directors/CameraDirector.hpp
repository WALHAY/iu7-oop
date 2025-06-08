#pragma once

#include <camera/loader/BaseCameraDirector.hpp>

class CameraDirector : public BaseCameraDirector
{
  public:
    CameraDirector() = delete;
    CameraDirector(std::shared_ptr<BaseCameraBuilder> builder);

    std::shared_ptr<Camera> create(std::shared_ptr<BaseCameraStreamReader> reader);

  private:
    std::shared_ptr<BaseCameraBuilder> builder;
};
