#pragma once

#include <camera/loader/BaseCameraStreamReader.hpp>

class TxtCameraReader : public BaseCameraStreamReader
{
  public:
    TxtCameraReader(std::shared_ptr<std::istream> stream);

	std::optional<Point> getLocation() override;
	std::optional<Point> getDirection() override;
  private:
    std::shared_ptr<std::istream> stream;
};
