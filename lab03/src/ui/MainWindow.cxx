#include "interface/commands/DrawCommand.hpp"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <ui/MainWindow.hpp>

#include <graphics/GraphicsFactory.hpp>
#include <graphics/QtGraphicsFactory.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graphicsScene = std::make_shared<QGraphicsScene>(this);

    ui->graphicsView->setScene(graphicsScene.get());
    ui->graphicsView->setMinimumSize(1280, 720);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    facade = std::make_shared<Facade>(graphicsScene);

    std::shared_ptr<DrawCommand> cmd = std::make_shared<DrawCommand>();
    facade->execute(cmd);
}

MainWindow::~MainWindow()
{
    delete ui;
}
