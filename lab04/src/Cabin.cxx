#include "../inc/Cabin.hpp"
#include <QDebug>

Cabin::Cabin(QObject *parent) : QObject(parent), state(UNLOCKED) {
  movingTimer.setSingleShot(true);

  connect(&door, SIGNAL(signalClosed()), this, SLOT(unlock()));
  connect(this, SIGNAL(signalLocked()), &door, SLOT(opening()));
}

void Cabin::lock() {
  if (state != MOVING && state != UNLOCKED) {
    return;
  }

  state = LOCKED;
  qDebug() << "Кабина заблокирована";
  emit signalLocked();
}

void Cabin::unlock() {
  if (state != LOCKED) {
    return;
  }

  state = UNLOCKED;
  qDebug() << "Кабина разблокирована";
  emit signalUnlocked();
}

void Cabin::move() {
  if (state != UNLOCKED) {
    return;
  }

  auto prevState = state;
  state = MOVING;
  qDebug() << (prevState == MOVING ? "Кабина продолжает движение"
                                   : "Кабина начала движение");
  movingTimer.start(1000);
}
