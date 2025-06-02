#pragma once

#include <QMainWindow>
#include <QGraphicsScene>

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
	std::shared_ptr<QGraphicsScene> scene;
    Ui::MainWindow *ui;
};
