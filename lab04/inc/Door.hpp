#pragma once

#include <QObject>
#include <QTimer>

class Door : public QObject
{
    Q_OBJECT;

  public:
    explicit Door(QObject *parent = nullptr);

  signals:
    void signalOpen();
    void signalClosed();

  public slots:
    void open();
    void close();
    void closing();
    void opening();

  private:
    enum State
    {
        CLOSED,
        CLOSING,
        OPEN,
        OPENING
    } state;

    QTimer openingTimer;
    QTimer openedTimer;
    QTimer closingTimer;
};
