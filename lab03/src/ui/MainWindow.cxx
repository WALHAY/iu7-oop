#include "interface/commands/DrawCommand.hpp"
#include "interface/commands/LoadCommand.hpp"
#include "interface/commands/RemoveCommand.hpp"
#include "interface/commands/SelectCommand.hpp"
#include "interface/commands/TransformCommand.hpp"
#include "interface/commands/UnSelectCommand.hpp"
#include "ui/RenderConfig.hpp"
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

#include <QAbstractItemView>
#include <graphics/GraphicsFactory.hpp>
#include <graphics/QtGraphicsFactory.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->sceneViewModel = new QStandardItemModel(this);
    ui->setupUi(this);

    graphicsScene = std::make_shared<QGraphicsScene>(this);

    ui->graphicsView->setScene(graphicsScene.get());
    ui->graphicsView->setFixedSize(RenderWidth, RenderHeight);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    graphicsScene->setBackgroundBrush(QBrush(QColor(0xFFFFFF)));

    sceneViewModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Object type")));
    sceneViewModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Id")));
    ui->sceneObjectTable->setModel(sceneViewModel);
    ui->sceneObjectTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->sceneObjectTable->verticalHeader()->setVisible(false);
    ui->sceneObjectTable->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);

    clearCameras();
    clearSceneTable();

    connect(ui->rotateXNegButton, &QPushButton::clicked, this, &MainWindow::rotateXNeg);
    connect(ui->rotateXPosButton, &QPushButton::clicked, this, &MainWindow::rotateXPos);
    connect(ui->rotateYNegButton, &QPushButton::clicked, this, &MainWindow::rotateYNeg);
    connect(ui->rotateYPosButton, &QPushButton::clicked, this, &MainWindow::rotateYPos);
    connect(ui->rotateZNegButton, &QPushButton::clicked, this, &MainWindow::rotateZNeg);
    connect(ui->rotateZPosButton, &QPushButton::clicked, this, &MainWindow::rotateZPos);

    connect(ui->moveXNegButton, &QPushButton::clicked, this, &MainWindow::moveXNeg);
    connect(ui->moveXPosButton, &QPushButton::clicked, this, &MainWindow::moveXPos);
    connect(ui->moveYNegButton, &QPushButton::clicked, this, &MainWindow::moveYNeg);
    connect(ui->moveYPosButton, &QPushButton::clicked, this, &MainWindow::moveYPos);
    connect(ui->moveZNegButton, &QPushButton::clicked, this, &MainWindow::moveZNeg);
    connect(ui->moveZPosButton, &QPushButton::clicked, this, &MainWindow::moveZPos);

    connect(ui->removeObjectButton, &QPushButton::clicked, this, &MainWindow::removeFromScene);

    connect(ui->cameraChoiceBox, &QComboBox::currentTextChanged, this, &MainWindow::changeCamera);
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

    bool parsed = true;
    auto id = text.toInt(&parsed);

    if (!parsed)
        return;

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

    clearCameras();
    clearSceneTable();

    auto cmd = std::make_shared<LoadCommand>(
        filename.toStdString(),
        [this](const ObjectType &type, const Object::id_type &id) { this->objectAdded(type, id); });
    facade->execute(cmd);
}

void MainWindow::clearSceneTable()
{
    auto model = ui->sceneObjectTable->model();
    if (model)
        model->removeRows(0, model->rowCount());
}

template <typename Cmd>
    requires std::derived_from<Cmd, BaseCommand>
void MainWindow::refreshSelectionCmd(const QItemSelection &selection, std::shared_ptr<CompositeCommand> command)
{
    for (const QModelIndex &add : selection.indexes())
    {
        if (add.column() != 1)
            continue;

        auto value = add.data().toUInt();

        command->add(std::make_shared<Cmd>(value));
    }
}

void MainWindow::refreshSelection(const QItemSelection &added, const QItemSelection &removed)
{
    auto composite = std::make_shared<CompositeCommand>();

    refreshSelectionCmd<SelectCommand>(added, composite);
    refreshSelectionCmd<UnSelectCommand>(removed, composite);

    facade->execute(composite);
}

void MainWindow::rotateXNeg()
{
    rotateAroundX(-RotationStep);
}

void MainWindow::rotateXPos()
{
    rotateAroundX(RotationStep);
}

void MainWindow::rotateYNeg()
{
    rotateAroundY(-RotationStep);
}

void MainWindow::rotateYPos()
{
    rotateAroundY(RotationStep);
}

void MainWindow::rotateZNeg()
{
    rotateAroundZ(-RotationStep);
}

void MainWindow::rotateZPos()
{
    rotateAroundZ(RotationStep);
}

void MainWindow::rotateAroundX(double angle)
{
    auto cosv = std::cos(angle / 180 * std::numbers::pi);
    auto sinv = std::sin(angle / 180 * std::numbers::pi);

    Matrix<double> transform = {{1, 0, 0, 0}, {0, cosv, -sinv, 0}, {0, sinv, cosv, 0}, {0, 0, 0, 1}};

    auto composite = std::make_shared<CompositeCommand>();

    composite->add(std::make_shared<TransformCommand>(transform));
    composite->add(std::make_shared<DrawCommand>());

    facade->execute(composite);
}

void MainWindow::rotateAroundY(double angle)
{
    auto cosv = std::cos(angle / 180 * std::numbers::pi);
    auto sinv = std::sin(angle / 180 * std::numbers::pi);

    Matrix<double> transform = {{cosv, 0, sinv, 0}, {0, 1, 0, 0}, {-sinv, 0, cosv, 0}, {0, 0, 0, 1}};

    auto composite = std::make_shared<CompositeCommand>();

    composite->add(std::make_shared<TransformCommand>(transform));
    composite->add(std::make_shared<DrawCommand>());

    facade->execute(composite);
}

void MainWindow::rotateAroundZ(double angle)
{
    auto cosv = std::cos(angle / 180 * std::numbers::pi);
    auto sinv = std::sin(angle / 180 * std::numbers::pi);

    Matrix<double> transform = {{cosv, -sinv, 0, 0}, {sinv, cosv, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

    auto composite = std::make_shared<CompositeCommand>();

    composite->add(std::make_shared<TransformCommand>(transform));
    composite->add(std::make_shared<DrawCommand>());

    facade->execute(composite);
}

void MainWindow::moveXNeg()
{
    move(-MoveStep, 0, 0);
}

void MainWindow::moveXPos()
{
    move(MoveStep, 0, 0);
}

void MainWindow::moveYNeg()
{
    move(0, -MoveStep, 0);
}

void MainWindow::moveYPos()
{
    move(0, MoveStep, 0);
}

void MainWindow::moveZNeg()
{
    move(0, 0, -MoveStep);
}

void MainWindow::moveZPos()
{
    move(0, 0, MoveStep);
}

void MainWindow::move(double x, double y, double z)
{
    Matrix<double> move = Matrix<double>::identity(4);
    move[3][0] = x;
    move[3][1] = y;
    move[3][2] = z;

    auto composite = std::make_shared<CompositeCommand>();

    composite->add(std::make_shared<TransformCommand>(move));
    composite->add(std::make_shared<DrawCommand>());

    facade->execute(composite);
}

void MainWindow::removeFromScene()
{
    auto composite = std::make_shared<CompositeCommand>();

    auto selectionModel = ui->sceneObjectTable->selectionModel();

    auto selectedIndices = selectionModel->selectedIndexes();

    for (const QModelIndex &index : selectedIndices)
    {
        if (index.column() != 1)
            continue;

        auto value = index.data();

        auto cameraId = ui->cameraChoiceBox->findText(value.toString());
        ui->cameraChoiceBox->removeItem(cameraId);

        ui->sceneObjectTable->model()->removeRow(index.row());

        composite->add(std::make_shared<RemoveCommand>(value.toUInt()));
    }

    composite->add(std::make_shared<DrawCommand>());

    facade->execute(composite);
}

MainWindow::~MainWindow()
{
    delete ui;
}
