#pragma once

#include "loader/BaseStreamReader.hpp"
#include <istream>

class TxtStreamReader : public BaseStreamReader
{
  public:
    TxtStreamReader(std::shared_ptr<std::istream> stream);

    std::optional<Point> getPoint() override;
    std::optional<Edge> getEdge() override;

  private:
    std::shared_ptr<std::istream> stream;
};
