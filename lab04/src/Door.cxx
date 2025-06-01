#include "../inc/Door.hpp"
#include "Config.hpp"
#include <QDebug>
#include <QThread>

Door::Door(QObject *parent) : QObject(parent), state(CLOSED)
{
    openedTimer.setSingleShot(true);
    openingTimer.setSingleShot(true);
    closingTimer.setSingleShot(true);

    connect(&openingTimer, &QTimer::timeout, this, &Door::open);
    connect(&openedTimer, &QTimer::timeout, this, &Door::closing);
    connect(&closingTimer, &QTimer::timeout, this, &Door::close);
}

void Door::open()
{
    if (state != OPENING)
    {
        return;
    }

    state = OPEN;
    qDebug() << "Дверь открыта";
    emit signalOpen();
    openedTimer.start(OPENED_TIME);
}

void Door::close()
{
    if (state != CLOSING)
    {
        return;
    }

    state = CLOSED;
    qDebug() << "Дверь закрыта";
    emit signalClosed();
}

void Door::opening()
{
    if (state != CLOSING && state != CLOSED)
    {
        return;
    }

    State previous = state;
    state = OPENING;

	auto time = OPENING_TIME;
    if (previous == CLOSING)
    {
        qDebug() << "Прервано закрытие двери";

		time -= closingTimer.remainingTime();
        closingTimer.stop();
    }

    qDebug() << "Дверь открывается";
    openingTimer.start(time);
}

void Door::closing()
{
    if (state != OPEN)
    {
        return;
    }

    state = CLOSING;
    qDebug() << "Дверь закрываается";
    closingTimer.start(OPENING_TIME);
}
