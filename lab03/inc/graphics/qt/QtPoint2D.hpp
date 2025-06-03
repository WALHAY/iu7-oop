#pragma once

#include <QPoint>
#include <graphics/abstract/Point2D.hpp>

class QtPoint2D : public Point2D
{
  public:
    QtPoint2D(int x, int y);

    int x() override;
    int y() override;

  private:
    QPoint point;
};
