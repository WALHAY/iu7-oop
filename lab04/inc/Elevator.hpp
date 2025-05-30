#pragma once

#include "Controller.hpp"
#include <Cabin.hpp>
#include <Door.hpp>
#include <QObject>

class Elevator : public QObject {
  Q_OBJECT

public:
  explicit Elevator(QObject *parent = nullptr);

  void moveFloor(int floor);

signals:

public slots:

private:
  Cabin cabin;
  Controller controller;
};
