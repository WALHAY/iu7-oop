#pragma once

#include <filesystem>

#include "stream/BaseFileLoader.hpp"

class TxtFileLoader : public BaseFileLoader
{
  public:
    ~TxtFileLoader() override = default;

    explicit TxtFileLoader(const std::filesystem::path &path);

    void open() override;
    void close() override;
    std::shared_ptr<std::ifstream> get() override;
};
