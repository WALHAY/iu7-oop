#include "ui_mainwindow.h"
#include <MainWindow.hpp>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <Settings.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    connect(this, &MainWindow::buttonClicked, &elevator, &Elevator::addFloor);

    ui->setupUi(this);
    generateUI();

    qDebug() << "Лифт на" << INITIAL_FLOOR << "этаже. Двери закрыты, кабина разблокирована";
}

void MainWindow::generateUI()
{
    for (auto i = FLOORS; i > 0; --i)
    {
        auto button = new QPushButton(this);
        button->setText(QString::number(i));
        button->setMinimumSize(QSize(70, 60));
        button->setMaximumSize(QSize(70, 60));
        ui->floorButtons->addWidget(button);

        connect(button, &QPushButton::pressed, this, [i, this]() { onButtonClicked(i); });
    }

    for (auto i = FLOORS; i > 0; --i)
    {
        auto button = new QPushButton(this);
        button->setText(QString::number(i));
        button->setMinimumSize(QSize(70, 60));
        button->setMaximumSize(QSize(70, 60));
        ui->cabinButtons->addWidget(button);

        connect(button, &QPushButton::pressed, this, [i, this]() { onButtonClicked(i); });
    }

    floorIndicators = new QButtonGroup();
    for (auto i = FLOORS; i > 0; --i)
    {
        auto button = new QRadioButton(this);
        button->setMinimumSize(QSize(70, 60));
        button->setText(QString::number(i));
        button->setEnabled(false);
        floorIndicators->addButton(button, i);
        ui->verticalLayout->addWidget(button);

        button->setStyleSheet(FLOOR_INDICATOR_STYLESHEET);
    }

    floorIndicators->button(INITIAL_FLOOR)->setChecked(true);
    connect(&elevator.controller, &Controller::signalOnFloor, this, &MainWindow::updateFloorIndicator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFloorIndicator(const int floor) const
{
    floorIndicators->button(floor)->setChecked(true);
}

void MainWindow::onButtonClicked(int floor)
{
    emit buttonClicked(floor);
}
