#pragma once

#include "camera/BaseCameraImpl.hpp"
#include "objects/Camera.hpp"

class PlainCamera : public Camera
{
    friend class ProjectionVisitor;
    friend class TransformVisitor;

  public:
    PlainCamera(std::shared_ptr<BaseCameraImpl> impl);

    void accept(std::shared_ptr<ObjectVisitor> visitor) override;

  private:
    std::shared_ptr<BaseCameraImpl> cameraImpl;
};
