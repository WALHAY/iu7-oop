#include "ui_mainwindow.h"
#include <MainWindow.hpp>
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
    // scene->setBackgroundBrush(QBrush(QColor(0xFFFFFF)));

    ui->graphicsView->setScene(scene.get());

    std::shared_ptr<GraphicsFactory> gf = std::make_shared<QtGraphicsFactory>(scene);

    auto canvas = gf->createCanvas(300, 300);

    auto a = gf->createPainter(canvas);

    auto b = gf->getGraphics();

    auto first = gf->createPoint2D(10, 10);
    auto second = gf->createPoint2D(300, 300);

    a->drawLine(first, second);
    b->displayCanvas(canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}
