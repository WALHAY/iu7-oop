#pragma once

#include <QObject>

class Controller : public QObject {
  Q_OBJECT;

public:
  explicit Controller(QObject *parent = nullptr);

signals:
  void signalMoving();
  void signalStopped();

public slots:
  void handleRequest();
  void handleMove();
  void handleStop();
  void handleWaiting();

private:
  enum State { WAITING, REQUEST_HANDLING, MOVE_HANDLING, STOP_HANDLING } state;
};
