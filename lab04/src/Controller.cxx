#include "../inc/Controller.hpp"
#include "Config.hpp"
#include <QDebug>

Controller::Controller(QObject *parent)
    : QObject(parent), state(WAITING), direction(UP), floor(INITIAL_FLOOR) {}

void Controller::handleRequest() {
  if (!q.empty()) {
    emit handleMove();
  }
}

void Controller::handleMove() {
  if (floor == q.front()) {
    emit signalStopped();
  } else if (floor < q.front()) {
    floor++;
    emit signalOnFloor(floor);
    qDebug() << "Этаж: " << floor;
    emit signalMoving();
  }
}

void Controller::handleStop() {}

void Controller::addRequest(int floor) {
  addToQueue(floor);
  emit handleRequest();
}

void Controller::addToQueue(int floor) { q.push(floor); }
