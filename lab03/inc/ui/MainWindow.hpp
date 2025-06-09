#pragma once

#include <QGraphicsScene>
#include <QMainWindow>
#include <QStandardItemModel>
#include <interface/Facade.hpp>
#include <QItemSelection>

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

    void refreshSelection(const QItemSelection &added, const QItemSelection &removed);

    void rotateLeft();

  signals:

  private slots:

  private:
    QStandardItemModel *sceneViewModel;
    std::shared_ptr<Facade> facade;
    std::shared_ptr<QGraphicsScene> graphicsScene;
    Ui::MainWindow *ui;
};
