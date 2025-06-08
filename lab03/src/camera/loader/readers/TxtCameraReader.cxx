#include <camera/loader/readers/TxtCameraReader.hpp>

TxtCameraReader::TxtCameraReader(std::shared_ptr<std::istream> stream) : stream(stream)
{
}

std::optional<Point> TxtCameraReader::getLocation() {
	return std::nullopt;
}

std::optional<Point> TxtCameraReader::getDirection() {
	return std::nullopt;
}
