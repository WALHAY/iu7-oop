#pragma once

#include "objects/impl/PlainCamera.hpp"
#include <graphics/GraphicsFactory.hpp>
#include <visitors/ObjectVisitor.hpp>

class DrawVisitor : public ObjectVisitor
{
    friend class Model;

  public:
    DrawVisitor(std::shared_ptr<GraphicsFactory> factory, std::shared_ptr<Canvas> canvas,
                std::shared_ptr<PlainCamera> camera);

    void visit(WireframeModel &model) override;
    void visit(PlainCamera &camera) override;

  private:
    std::shared_ptr<GraphicsFactory> graphicsFactory;
    std::shared_ptr<Canvas> canvas;
    std::shared_ptr<PlainCamera> camera;
};
