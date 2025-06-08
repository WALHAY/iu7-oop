#include <camera/loader/BaseCameraDirector.hpp>

BaseCameraDirector::~BaseCameraDirector() = default;

BaseCameraDirector::BaseCameraDirector(std::shared_ptr<BaseCameraBuilder> builder) : builder(builder)
{
}
