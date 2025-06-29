#include <camera/loader/directors/CameraDirector.hpp>

CameraDirector::CameraDirector(std::shared_ptr<BaseCameraBuilder> builder,
                               std::shared_ptr<BaseCameraStreamReader> reader)
{
	this->reader = reader;
    this->builder = builder;
}

std::shared_ptr<Camera> CameraDirector::create()
{
    builder->build();

    auto location = reader->getLocation();
    auto direction = reader->getDirection();

    if (location)
        builder->buildLocation(*location);

    if (direction)
        builder->buildDirection(*direction);

    return builder->get();
}
