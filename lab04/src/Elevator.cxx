#include "../inc/Elevator.hpp"

Elevator::Elevator(QObject *parent) : QObject(parent)
{
    connect(&controller, &Controller::signalMoveCabin, &cabin, &Cabin::move);
    connect(&controller, &Controller::signalStopCabin, &cabin, &Cabin::lock);
    connect(&cabin.movingTimer, &QTimer::timeout, &controller, &Controller::handleMove);
    connect(&cabin, &Cabin::signalUnlocked, &controller, &Controller::handleMove);
}

void Elevator::addFloor(floor_type floor)
{
    emit controller.handleRequest(floor);
}
