#pragma once

#include <QObject>
#include <QTimer>

class Controller : public QObject
{
    Q_OBJECT;

  public:
	using floor_type = int;

    explicit Controller(QObject *parent = nullptr);

  signals:
    void signalMoveCabin();
    void signalStopCabin();

    void signalMove();
    void signalStop();

    void signalOnFloor(floor_type);

    void signalNewRequest();
    void signalNoRequests();

  public slots:
    void handleMove();
    void handleStop();
    void handleWait();
    void handleRequest(floor_type floor);

  private:
    enum State
    {
        WAITING,
        REQUEST_HANDLING,
        MOVE_HANDLING,
        STOP_HANDLING
    } state;
    floor_type floor;
    enum Direction : floor_type
    {
        UP = 1,
        DOWN = -1
    } direction;

    std::deque<floor_type> requests;

    void addRequest(floor_type floor);
};
