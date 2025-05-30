#pragma once

#include <Cabin.hpp>
#include <Door.hpp>
#include <QObject>

class Elevator : public QObject {
  Q_OBJECT

public:
  explicit Elevator(QObject *parent = nullptr);

signals:

public slots:

private:
  Door door;
  Cabin cabin;
};
