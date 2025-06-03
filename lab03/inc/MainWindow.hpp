#pragma once

#include <QGraphicsScene>
#include <QMainWindow>
#include <interface/Facade.hpp>

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

  signals:

  private slots:

  private:
    std::shared_ptr<Facade> facade;
    std::shared_ptr<QGraphicsScene> scene;
    Ui::MainWindow *ui;
};
