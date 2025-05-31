#pragma once

#include <QObject>
#include <QTimer>

class Controller : public QObject
{
    Q_OBJECT;

  public:
    explicit Controller(QObject *parent = nullptr);

  signals:
    void signalMoveCabin();
    void signalStopCabin();

    void signalMove();
    void signalStop();

    void signalOnFloor(int);

    void signalNewRequest();
    void signalNoRequests();

  public slots:
    void handleMove();
    void handleStop();
    void handleWait();

    void handleRequest(int floor);

  private:
    enum State
    {
        WAITING,
        REQUEST_HANDLING,
        MOVE_HANDLING,
        STOP_HANDLING
    } state;
    int floor;
    enum Direction : int
    {
        UP = 1,
        DOWN = -1
    } direction;

    std::queue<int> requests;

    void addToQueue(int floor);
};
