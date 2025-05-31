#include "MainWindow.hpp"

#include "Config.hpp"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  connect(this, &MainWindow::buttonClicked, &elevator, &Elevator::addFloor);

  ui->setupUi(this);
  generateUI();

  qDebug() << "Лифт на этаже " << INITIAL_FLOOR
           << "Двери закрыты, кабина готова к движению";
}

void MainWindow::generateUI() {
  for (auto i = FLOORS; i > 0; --i) {
    auto btn = new QPushButton(this);
    btn->setText(QString::number(i));
    btn->setMinimumSize(QSize(70, 60));
    btn->setMaximumSize(QSize(70, 60));
    ui->floorButtons->addWidget(btn);

    connect(btn, &QPushButton::pressed, this,
            [i, this]() { onButtonClicked(i); });
  }

  // Cabin Buttons
  for (auto i = FLOORS; i > 0; --i) {
    auto btn = new QPushButton(this);
    btn->setText(QString::number(i));
    btn->setMinimumSize(QSize(70, 60));
    btn->setMaximumSize(QSize(70, 60));
    ui->cabinButtons->addWidget(btn);

    connect(btn, &QPushButton::pressed, this,
            [i, this]() { onButtonClicked(i); });
  }

  floorIndicators = new QButtonGroup();
  for (auto i = FLOORS; i > 0; --i) {
    auto btn = new QRadioButton(this);
    btn->setMinimumSize(QSize(70, 60));
    btn->setText(QString::number(i));
    btn->setEnabled(false);
    floorIndicators->addButton(btn, i);
    ui->verticalLayout->addWidget(btn);

    btn->setStyleSheet(FLOOR_INDICATOR_STYLESHEET);
  }

  floorIndicators->button(INITIAL_FLOOR)->setChecked(true);
  connect(&elevator.controller, &Controller::signalOnFloor, this,
          &MainWindow::updateFloorIndicator);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::updateFloorIndicator(const int floor) const {
  floorIndicators->button(floor)->setChecked(true);
}

void MainWindow::onButtonClicked(int floor) { emit buttonClicked(floor); }
