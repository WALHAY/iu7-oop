#pragma once

#include "Canvas.hpp"
#include <memory>

class Graphics
{
  public:
    virtual ~Graphics() = 0;

    virtual void displayCanvas(std::shared_ptr<Canvas> canvas) = 0;
};

inline Graphics::~Graphics() = default;
