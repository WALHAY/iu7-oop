#include <istream>
#include <scene/loader/SceneReader.hpp>
#include <sstream>

SceneReader::SceneReader(std::shared_ptr<std::istream> stream) : stream(stream)

{
}

std::optional<ObjectType> SceneReader::getType()
{
    bool hasType = false;
    std::streampos position = stream->tellg();

    std::string line;
    getline(*stream, line);

    std::string type;
    std::stringstream ss(line);
    if (ss >> type)
        hasType = true;

    if (!hasType)
    {
        stream->seekg(position);
        return std::nullopt;
    }

    if (type == "Model")
        return std::make_optional<ObjectType>(ObjectType::MODEl);
    else if (type == "Camera")
        return std::make_optional<ObjectType>(ObjectType::CAMERA);

    return std::nullopt;
}
