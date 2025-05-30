#pragma once

#include "Door.hpp"
#include <QObject>

class Cabin : public QObject {
  Q_OBJECT;

public:
  explicit Cabin(QObject *parent = nullptr);

signals:
  void signalLocked();
  void signalUnlocked();

public slots:
  void lock();
  void unlock();
  void move();

private:
  enum State { LOCKED, UNLOCKED, MOVING } state;

  Door door;
  QTimer movingTimer;
};
