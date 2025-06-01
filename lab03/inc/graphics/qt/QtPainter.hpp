#pragma once

#include <graphics/abstract/Painter.hpp>

class QtPainter : public Painter {
public:
	
    void drawLine(const Point2D &first, const Point2D &second) override;
private:
	
};

