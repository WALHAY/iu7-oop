#include "interface/commands/DrawCommand.hpp"
#include "ui_mainwindow.h"
#include <ui/MainWindow.hpp>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

#include <graphics/GraphicsFactory.hpp>
#include <graphics/QtGraphicsFactory.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = std::make_shared<QGraphicsScene>(this);

    ui->graphicsView->setScene(scene.get());
	ui->graphicsView->setMinimumSize(1280, 720);

    facade = std::make_shared<Facade>(scene);

    std::shared_ptr<DrawCommand> cmd = std::make_shared<DrawCommand>();
    facade->execute(cmd);
}

MainWindow::~MainWindow()
{
    delete ui;
}
