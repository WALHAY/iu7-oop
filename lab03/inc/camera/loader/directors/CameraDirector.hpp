#pragma once

#include "camera/loader/BaseCameraStreamReader.hpp"
#include <camera/loader/BaseCameraDirector.hpp>
#include <camera/loader/BaseCameraBuilder.hpp>

class CameraDirector : public BaseCameraDirector
{
  public:
    CameraDirector() = delete;
    CameraDirector(std::shared_ptr<BaseCameraBuilder> builder, std::shared_ptr<BaseCameraStreamReader> reader);

    std::shared_ptr<Camera> create() override;

  private:
    std::shared_ptr<BaseCameraBuilder> builder;
    std::shared_ptr<BaseCameraStreamReader> reader;
};
