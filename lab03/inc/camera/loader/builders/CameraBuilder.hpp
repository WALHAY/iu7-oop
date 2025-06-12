#pragma once

#include "camera/BaseCameraImpl.hpp"
#include <camera/loader/BaseCameraBuilder.hpp>

class CameraBuilder : public BaseCameraBuilder {
public:
	void build() override;

	void buildLocation(const Point &location) override;
	void buildDirection(const Point &direction) override;

	std::shared_ptr<Camera> get() override;
private:
	std::shared_ptr<BaseCameraImpl> cameraImpl;
};

