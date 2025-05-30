#pragma once

#include <QObject>

class Cabin : public QObject {
  Q_OBJECT;

public:
  explicit Cabin(QObject *parent = nullptr);

signals:

public slots:

private:
  enum State { LOCKED, UNLOCKED, MOVING } state;
};
