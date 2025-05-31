#pragma once

#include <QObject>
#include <QTimer>

class Controller : public QObject {
  Q_OBJECT;

  friend class Elevator;

public:
  explicit Controller(QObject *parent = nullptr);

signals:
  void signalMoving();
  void signalStopped();
  void signalOnFloor(int);

public slots:
  void handleRequest();
  void handleMove();
  void handleStop();

private slots:
  void addRequest(int floor);

private:
  enum State { WAITING, REQUEST_HANDLING, MOVE_HANDLING, STOP_HANDLING } state;
  int floor;
  enum Direction { UP = 1, DOWN = -1 } direction;

  std::queue<int> q;

  void addToQueue(int floor);
};
