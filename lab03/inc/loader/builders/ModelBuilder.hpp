#pragma once

#include "loader/BaseBuilder.hpp"
#include "wireframe/Wireframe.hpp"

class ModelBuilder : public BaseBuilder
{
  public:
    void build() override;

    void buildEdge(const Edge &edge) override;
    void buildPoint(const Point &location) override;

    std::shared_ptr<Object> get() override;

  private:
    std::shared_ptr<Wireframe> wireframe = nullptr;

    bool validateBuild();
};
