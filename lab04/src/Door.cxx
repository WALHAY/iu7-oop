#include "../inc/Door.hpp"
#include <QDebug>
#include <QThread>

Door::Door(QObject *parent) : QObject(parent), state(CLOSED) {
  openTimer.setSingleShot(true);
  openingTimer.setSingleShot(true);
  closingTimer.setSingleShot(true);
  openTimer.setInterval(1000);

  connect(&openingTimer, &QTimer::timeout, this, &Door::open);
  connect(this, SIGNAL(signalOpen()), &openTimer, SLOT(start()));
  connect(&openTimer, &QTimer::timeout, this, &Door::closing);
  connect(&closingTimer, &QTimer::timeout, this, &Door::close);
}

void Door::open() {
  if (state != OPENING) {
    return;
  }

  state = OPEN;
  qDebug() << "Дверь открыта";
  emit signalOpen();
}

void Door::close() {
  if (state != CLOSING) {
    return;
  }

  state = CLOSED;
  qDebug() << "Дверь закрыта";
  emit signalClosed();
}

void Door::opening() {
  if (state != CLOSING && state != CLOSED) {
    return;
  }

  State previous = state;
  state = OPENING;

  if (previous == CLOSING) {
    qDebug() << "Прервано закрытие двери";

    closingTimer.stop();
  }

  qDebug() << "Дверь открывается";
  openingTimer.start(1000);
}

void Door::closing() {
  if (state != OPEN) {
    return;
  }

  state = CLOSING;
  qDebug() << "Дверь закрываается";
  closingTimer.start(1000);
}
