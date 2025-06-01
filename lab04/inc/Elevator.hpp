#pragma once

#include "Controller.hpp"
#include <Cabin.hpp>
#include <Door.hpp>
#include <QObject>

class Elevator : public QObject
{
    Q_OBJECT;

    friend class MainWindow;

  public:
	using floor_type = Controller::floor_type;

    explicit Elevator(QObject *parent = nullptr);

  signals:

  public slots:
    void addFloor(floor_type floor);

  private:
    Cabin cabin;
    Controller controller;
};
