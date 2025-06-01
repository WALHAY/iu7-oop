#include "../inc/Cabin.hpp"
#include "Config.hpp"
#include <QDebug>

Cabin::Cabin(QObject *parent) : QObject(parent), state(UNLOCKED)
{
    movingTimer.setSingleShot(true);

    connect(this, &Cabin::signalLocked, &door, &Door::opening);
    connect(&door, &Door::signalClosed, this, &Cabin::unlock);
}

void Cabin::lock()
{
    if (state != MOVING && state != UNLOCKED && state != LOCKED)
    {
        return;
    }

    auto prev = state;
    state = LOCKED;
    if (prev != LOCKED)
        qDebug() << "Кабина заблокирована";
    emit signalLocked();
}

void Cabin::unlock()
{
    if (state != LOCKED)
    {
        return;
    }

    state = UNLOCKED;
    qDebug() << "Кабина разблокирована";
    emit signalUnlocked();
}

void Cabin::move()
{
    if (state != UNLOCKED && state != MOVING)
    {
        return;
    }

    auto prevState = state;
    state = MOVING;
	if(prevState == UNLOCKED)
		qDebug() << "Кабина начала движение";
    movingTimer.start(MOVE_TIME);
}
