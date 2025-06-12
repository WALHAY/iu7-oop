#include <QDebug>
#include "objects/impl/PlainCamera.hpp"
#include <camera/loader/builders/CameraBuilder.hpp>
#include <camera/CameraImpl.hpp>

void CameraBuilder::build() {
	this->cameraImpl = std::make_shared<CameraImpl>(Point(0, 0, 0));
}

void CameraBuilder::buildDirection(const Point& direction)
{
	if(cameraImpl == nullptr)
		return;

	this->cameraImpl->setForward(direction);
}

void CameraBuilder::buildLocation(const Point& location)
{
	if(cameraImpl == nullptr)
		return;

	this->cameraImpl->setLocation(location);
}

std::shared_ptr<Camera> CameraBuilder::get() {
	return std::make_shared<PlainCamera>(cameraImpl);
}
