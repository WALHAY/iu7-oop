#include "../inc/Controller.hpp"
#include "Config.hpp"
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent), state(WAITING), direction(UP), floor(INITIAL_FLOOR)
{
    connect(this, &Controller::signalNewRequest, this, &Controller::handleMove);
    connect(this, &Controller::signalStop, this, &Controller::handleStop);
    connect(this, &Controller::signalNoRequests, this, &Controller::handleWait);
}

void Controller::handleWait()
{
    state = WAITING;

    qDebug() << "Контроллер ожидает цели";
}

void Controller::handleMove()
{
    if (state != REQUEST_HANDLING && state != MOVE_HANDLING && state != STOP_HANDLING)
    {
        return;
    }

    if (state == MOVE_HANDLING)
    {
        floor += direction;
        emit signalOnFloor(floor);
    }

    state = MOVE_HANDLING;

    if (floor < requests.front() && direction == DOWN)
        direction = UP;
    else if (floor > requests.front() && direction == UP)
        direction = DOWN;

    if (requests.empty())
    {
        qDebug() << "У контроллера отстуствуют цели";

        emit signalNoRequests();
    }
    else
    {
        if (floor == requests.front())
        {
            emit signalStop();
        }
        else
        {
            emit signalMove();
        }
    }
}

void Controller::handleStop()
{
    if (state != REQUEST_HANDLING && state != MOVE_HANDLING && state != STOP_HANDLING)
    {
        return;
    }

    state = STOP_HANDLING;
    if (requests.empty())
        emit signalNoRequests();
    else if (floor == requests.front())
    {
        requests.pop();
        if (requests.empty())
            emit signalNoRequests();
        else
            emit signalMove();
    }
}

void Controller::handleRequest(int floor)
{
    auto prev = state;
    state = REQUEST_HANDLING;

    addToQueue(floor);
    if (this->floor == floor)
        emit signalStop();
    else if (prev == WAITING)
    {
        emit signalNewRequest();
    };
}

void Controller::addToQueue(int floor)
{
    requests.push(floor);
}
