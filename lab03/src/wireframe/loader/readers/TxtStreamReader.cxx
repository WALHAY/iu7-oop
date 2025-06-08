#include <sstream>
#include <wireframe/loader/readers/TxtModelReader.hpp>

TxtModelReader::TxtModelReader(std::shared_ptr<std::istream> stream) : stream(stream)
{
}

std::optional<Edge> TxtModelReader::getEdge()
{
    bool hasEdge = false;
    std::streampos position = stream->tellg();

    std::string line;
    getline(*stream, line);

    size_t first;
    size_t second;
    std::stringstream ss(line);
    if (ss >> first >> second)
        hasEdge = true;

    if (!hasEdge)
    {
        stream->seekg(position);
        return std::nullopt;
    }

    return std::make_optional<Edge>(first, second);
}

std::optional<Point> TxtModelReader::getPoint()
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
