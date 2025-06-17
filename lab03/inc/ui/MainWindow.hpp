#pragma once

#include <QGraphicsScene>
#include <QItemSelection>
#include <QMainWindow>
#include <QStandardItemModel>
#include <interface/Facade.hpp>
#include <interface/commands/CompositeCommand.hpp>

QT_BEGIN_NAMESPACE

namespace Ui
{
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void objectAdded(ObjectType, Object::id_type);

    void addCamera(Object::id_type id);
    void changeCamera(const QString &text);
    void clearCameras();

    void loadSceneDialog();
    void clearSceneTable();

    void refreshSelection(const QItemSelection &added, const QItemSelection &removed);

    void rotateAroundX(double angle);
    void rotateAroundY(double angle);
    void rotateAroundZ(double angle);

    void rotateXNeg();
    void rotateXPos();
    void rotateYNeg();
    void rotateYPos();
    void rotateZNeg();
    void rotateZPos();

    void move(double x, double y, double z);

    void moveXNeg();
    void moveXPos();
    void moveYNeg();
    void moveYPos();
    void moveZNeg();
    void moveZPos();

	void removeFromScene();

  private:
    QStandardItemModel *sceneViewModel;
    std::shared_ptr<Facade> facade;
    std::shared_ptr<QGraphicsScene> graphicsScene;
    Ui::MainWindow *ui;

    template <typename Cmd>
        requires std::derived_from<Cmd, BaseCommand>
    void refreshSelectionCmd(const QItemSelection &selection, std::shared_ptr<CompositeCommand> command);
};
