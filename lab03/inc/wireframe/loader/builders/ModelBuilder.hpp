#pragma once

#include "wireframe/Wireframe.hpp"
#include "wireframe/loader/BaseModelBuilder.hpp"

class ModelBuilder : public BaseModelBuilder
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
