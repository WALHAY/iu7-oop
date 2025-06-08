#pragma once

#include "scene/loader/BaseSceneStreamReader.hpp"
#include <filesystem>
#include <optional>

class TxtSceneReader : public BaseSceneStreamReader
{
  public:
    TxtSceneReader(std::shared_ptr<std::istream> stream);

    std::optional<std::filesystem::path> getModelPath() override;
    std::optional<std::filesystem::path> getCameraPath() override;
  private:
    std::shared_ptr<std::istream> stream;
};
