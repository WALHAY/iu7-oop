#include <camera/loader/readers/TxtCameraReader.hpp>
#include <istream>
#include <sstream>

TxtCameraReader::TxtCameraReader(std::shared_ptr<std::istream> stream) : stream(stream)
{
}

std::optional<Point> TxtCameraReader::getLocation()
{
    bool hasPoint = false;
    std::streampos position = stream->tellg();

    std::string line;
    getline(*stream, line);

    double x;
    double y;
    double z;
    std::stringstream ss(line);
    if (ss >> x >> y >> z)
        hasPoint = true;

    if (!hasPoint)
    {
        stream->seekg(position);
        return std::nullopt;
    }

    return std::make_optional<Point>(x, y, z);
}

std::optional<Point> TxtCameraReader::getDirection()
{
    bool hasPoint = false;
    std::streampos position = stream->tellg();

    std::string line;
    getline(*stream, line);

    double x;
    double y;
    double z;
    std::stringstream ss(line);
    if (ss >> x >> y >> z)
        hasPoint = true;

    if (!hasPoint)
    {
        stream->seekg(position);
        return std::nullopt;
    }

    return std::make_optional<Point>(x, y, z);
}
