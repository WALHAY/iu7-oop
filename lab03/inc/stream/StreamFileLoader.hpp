#pragma once

#include <memory>
#include "stream/BaseFileLoader.hpp"
#include "stream/BaseStreamLoader.hpp"

class StreamFileLoader : public BaseStreamLoader
{
  public:
    ~StreamFileLoader() override = default;

    explicit StreamFileLoader(std::shared_ptr<BaseFileLoader> fileLoader);

    std::shared_ptr<std::istream> getStream() override;
    void closeStream() override;

  private:
    std::shared_ptr<BaseFileLoader> fileLoader;
};
