#pragma once

#include <filesystem>
#include <memory>
#include <optional>
class BaseSceneStreamReader
{
  public:
	virtual ~BaseSceneStreamReader() = 0;

    virtual std::optional<std::filesystem::path> getModelPath() = 0;
    virtual std::optional<std::filesystem::path> getCameraPath() = 0;
};

inline BaseSceneStreamReader::~BaseSceneStreamReader() = default;
