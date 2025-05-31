#pragma once

#include "Controller.hpp"
#include <Cabin.hpp>
#include <Door.hpp>
#include <QObject>

class Elevator : public QObject
{
    Q_OBJECT

    friend class MainWindow;
    friend class Cabin;

  public:
    explicit Elevator(QObject *parent = nullptr);

  signals:

  public slots:
    void addFloor(int floor);

  private:
    Cabin cabin;
    Controller controller;
};
