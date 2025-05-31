#include "../inc/Cabin.hpp"
#include <QDebug>

Cabin::Cabin(QObject *parent) : QObject(parent), state(UNLOCKED)
{
    movingTimer.setSingleShot(true);

    connect(&door, &Door::signalClosed, this, &Cabin::unlock);
    connect(this, &Cabin::signalLocked, &door, &Door::opening);
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
    qDebug() << (prevState == MOVING ? "Кабина продолжает движение" : "Кабина начала движение");
    movingTimer.start(1000);
}
