#include "interface/commands/DrawCommand.hpp"
#include "interface/commands/LoadCommand.hpp"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <interface/commands/ChangeCameraCommand.hpp>
#include <interface/commands/CompositeCommand.hpp>
#include <ui/MainWindow.hpp>

#include <graphics/GraphicsFactory.hpp>
#include <graphics/QtGraphicsFactory.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->sceneViewModel = new QStandardItemModel(this);
    ui->setupUi(this);

    graphicsScene = std::make_shared<QGraphicsScene>(this);

    ui->graphicsView->setScene(graphicsScene.get());
    ui->graphicsView->setMinimumSize(1280, 720);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    sceneViewModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Object type")));
    sceneViewModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Id")));
    ui->sceneObjectTable->setModel(sceneViewModel);
    ui->sceneObjectTable->verticalHeader()->setVisible(false);

    clearCameras();

    connect(ui->cameraChoiceBox, &QComboBox::currentTextChanged, this, &MainWindow::changeCamera);


    facade = std::make_shared<Facade>(graphicsScene);

    auto cmd = std::make_shared<LoadCommand>(
        "./scene.txt", [this](const ObjectType &type, const Object::id_type &id) { this->objectAdded(type, id); });
    facade->execute(cmd);
}

void MainWindow::objectAdded(ObjectType type, Object::id_type id)
{
    QList<QStandardItem *> row;
    row << new QStandardItem(QString(type == ObjectType::CAMERA ? "Camera" : "Model"));
    row << new QStandardItem(QString::number(id));
    this->sceneViewModel->appendRow(row);
    if (type == ObjectType::CAMERA)
        addCamera(id);
}

void MainWindow::addCamera(Object::id_type id)
{
    ui->cameraChoiceBox->addItem(QString::number(id));
}

void MainWindow::changeCamera(const QString &text)
{
    auto id = text.toInt();

	if(id == -1)
	{
		ui->graphicsView->scene()->clear();
		return;
	}

    auto compositeCmd = std::make_shared<CompositeCommand>();

    compositeCmd->add(std::make_shared<ChangeCameraCommand>(id));
    compositeCmd->add(std::make_shared<DrawCommand>());

    facade->execute(compositeCmd);
}

void MainWindow::clearCameras()
{
    ui->cameraChoiceBox->clear();
    ui->cameraChoiceBox->addItem(QString::number(-1));
}

MainWindow::~MainWindow()
{
    delete ui;
}
