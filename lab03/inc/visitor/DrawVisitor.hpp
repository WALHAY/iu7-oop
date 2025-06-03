#pragma once

#include <graphics/GraphicsFactory.hpp>
#include <visitor/ObjectVisitor.hpp>

class DrawVisitor : public ObjectVisitor
{
    friend class Model;

  public:
    DrawVisitor(std::shared_ptr<GraphicsFactory> factory, std::shared_ptr<Canvas> canvas,
                std::shared_ptr<Camera> camera);

    void visit(Model &model) override;
    void visit(Camera &camera) override;

  private:
    std::shared_ptr<GraphicsFactory> graphicsFactory;
    std::shared_ptr<Canvas> canvas;
    std::shared_ptr<Camera> camera;
};
