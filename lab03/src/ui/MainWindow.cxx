#include "interface/commands/DrawCommand.hpp"
#include "interface/commands/LoadCommand.hpp"
#include "interface/commands/SelectCommand.hpp"
#include "interface/commands/TransformCommand.hpp"
#include "interface/commands/UnSelectCommand.hpp"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <interface/commands/ChangeCameraCommand.hpp>
#include <interface/commands/CompositeCommand.hpp>
#include <numbers>
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
    ui->sceneObjectTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->sceneObjectTable->verticalHeader()->setVisible(false);

    clearCameras();

    connect(ui->cameraChoiceBox, &QComboBox::currentTextChanged, this, &MainWindow::changeCamera);
    connect(ui->rotateLeftButton, &QPushButton::clicked, this, &MainWindow::rotateLeft);
    connect(ui->loadSceneButton, &QPushButton::clicked, this, &MainWindow::loadSceneDialog);
    connect(ui->sceneObjectTable->selectionModel(), &QItemSelectionModel::selectionChanged, this,
            &MainWindow::refreshSelection);

    facade = std::make_shared<Facade>(graphicsScene);
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
    if (text.contains("None"))
    {
        ui->graphicsView->scene()->clear();
        return;
    }

    auto id = text.toInt();

    auto compositeCmd = std::make_shared<CompositeCommand>();

    compositeCmd->add(std::make_shared<ChangeCameraCommand>(id));
    compositeCmd->add(std::make_shared<DrawCommand>());

    facade->execute(compositeCmd);
}

void MainWindow::clearCameras()
{
    ui->cameraChoiceBox->clear();
    ui->cameraChoiceBox->addItem(QString("None"));
}

void MainWindow::loadSceneDialog()
{
    auto filename = QFileDialog::getOpenFileName(this, "Path to scene", "Scene *.txt");

    if (filename.isEmpty())
        return;

    auto cmd = std::make_shared<LoadCommand>(
        filename.toStdString(),
        [this](const ObjectType &type, const Object::id_type &id) { this->objectAdded(type, id); });
    facade->execute(cmd);
}

void MainWindow::refreshSelection(const QItemSelection &added, const QItemSelection &removed)
{
    auto composite = std::make_shared<CompositeCommand>();

    for (const QModelIndex &add : added.indexes())
    {
        if (add.column() != 1)
            continue;

        auto value = add.data().toUInt();

        composite->add(std::make_shared<SelectCommand>(value));
    }

    for (const QModelIndex &removed : removed.indexes())
    {
        if (removed.column() != 1)
            continue;

        auto value = removed.data().toUInt();

        composite->add(std::make_shared<UnSelectCommand>(value));
    }

    facade->execute(composite);
}

void MainWindow::rotateLeft()
{
    double angle = 2;
    auto cosv = std::cos(angle / 180 * std::numbers::pi);
    auto sinv = std::sin(angle / 180 * std::numbers::pi);

    Matrix<double> transform = {{1, 0, 0, 0}, {0, cosv, -sinv, 0}, {0, sinv, cosv, 0}, {0, 0, 0, 1}};

    auto composite = std::make_shared<CompositeCommand>();

    composite->add(std::make_shared<TransformCommand>(transform));
    composite->add(std::make_shared<DrawCommand>());

    facade->execute(composite);
}

MainWindow::~MainWindow()
{
    delete ui;
}
