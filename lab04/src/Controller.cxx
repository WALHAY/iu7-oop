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
    if (state != MOVE_HANDLING && state != STOP_HANDLING)
    {
        return;
    }

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
        qDebug() << "Кабина двигается с" << floor << "на" << floor + direction << "этаж";

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
            emit signalMoveCabin();
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
        requests.pop_front();
        emit signalStopCabin();
    }
    else
        emit signalMove();
}

void Controller::handleRequest(floor_type floor)
{
    auto prev = state;
    state = REQUEST_HANDLING;

    addRequest(floor);
    if (this->floor == floor)
        emit signalStop();
    else if (prev == WAITING)
        emit signalNewRequest();
}

void Controller::addRequest(floor_type floor)
{
    if (std::ranges::find(requests, floor) != requests.end())
    {
        return;
    }

    requests.push_back(floor);
    std::ranges::sort(requests.begin(), requests.end(), [this](const floor_type &a, const floor_type &b) {
        if (direction == UP)
        {
            if (a >= this->floor && b >= this->floor)
                return a < b;
            if (a < this->floor && b < this->floor)
                return a > b;
            return a >= this->floor;
        }
        else
        {
            if (a <= this->floor && b <= this->floor)
                return a > b;
            if (a > this->floor && b > this->floor)
                return a < b;
            return a <= this->floor;
        }
    });
}
