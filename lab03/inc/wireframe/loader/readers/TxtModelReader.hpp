#pragma once

#include "wireframe/loader/BaseModelStreamReader.hpp"
#include <istream>

class TxtModelReader : public BaseModelStreamReader
{
  public:
    TxtModelReader(std::shared_ptr<std::istream> stream);

    std::optional<Point> getPoint() override;
    std::optional<Edge> getEdge() override;

  private:
    std::shared_ptr<std::istream> stream;
};
