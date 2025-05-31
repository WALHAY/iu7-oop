#include "../inc/Elevator.hpp"

Elevator::Elevator(QObject *parent) : QObject(parent) {
  connect(&controller, &Controller::signalMoving, &cabin, &Cabin::move);
  connect(&cabin.movingTimer, &QTimer::timeout, &controller,
          &Controller::handleMove);
  connect(&controller, &Controller::signalStopped, &cabin, &Cabin::lock);
}

void Elevator::addFloor(int floor) { emit controller.addRequest(floor); }
