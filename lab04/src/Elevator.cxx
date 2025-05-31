#include "../inc/Elevator.hpp"

Elevator::Elevator(QObject *parent) : QObject(parent)
{
    connect(&controller, &Controller::signalMoveCabin, &cabin, &Cabin::move);
    connect(&cabin.movingTimer, &QTimer::timeout, &controller, &Controller::handleMove);
    connect(&controller, &Controller::signalStopCabin, &cabin, &Cabin::lock);
}

void Elevator::addFloor(int floor)
{
    emit controller.handleRequest(floor);
}
