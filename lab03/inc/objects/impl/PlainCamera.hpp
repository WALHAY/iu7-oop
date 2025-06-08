#pragma once

#include "camera/CameraImpl.hpp"
#include "objects/Camera.hpp"

class PlainCamera : public Camera
{
  public:
    PlainCamera(std::shared_ptr<CameraImpl> impl);

	void accept(std::shared_ptr<ObjectVisitor> visitor) override;
  private:
    std::shared_ptr<CameraImpl> cameraImpl;
};
