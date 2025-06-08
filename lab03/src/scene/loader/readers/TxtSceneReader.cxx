#include <scene/loader/readers/TxtSceneReader.hpp>
#include <sstream>

TxtSceneReader::TxtSceneReader(std::shared_ptr<std::istream> stream) : stream(stream)
{
}

std::optional<std::filesystem::path> TxtSceneReader::getCameraPath()
{
    if (stream == nullptr)
        return std::nullopt;

    auto position = stream->tellg();

    bool success = false;

    std::string line;
    getline(*stream, line);

    std::string type;
    std::string separator;
    std::filesystem::path filename;

    std::stringstream ss(line);
    if (ss >> type >> separator >> filename)
        success = type == "Camera";

    if (!success)
    {
        stream->seekg(position);
        return std::nullopt;
    }

    return std::make_optional<std::filesystem::path>(filename);
}

std::optional<std::filesystem::path> TxtSceneReader::getModelPath()
{
    if (stream == nullptr)
        return std::nullopt;

    auto position = stream->tellg();

    bool success = false;

    std::string line;
    getline(*stream, line);

    std::string type;
    std::string separator;
    std::filesystem::path filename;

    std::stringstream ss(line);
    if (ss >> type >> separator >> filename)
    {
        success = type == "Model";
    }

    if (!success)
    {
        stream->seekg(position);
        return std::nullopt;
    }

    return std::make_optional<std::filesystem::path>(filename);
}
