#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>

#include "Elevator.hpp"

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
        void buttonClicked(int floor);

private slots:
    void updateFloorIndicator(int floor) const;
    void onButtonClicked(int floor);

private:
    void generateUI();

private:
    Ui::MainWindow *ui;
    QButtonGroup* floorIndicators;

    Elevator elevator;

};
#endif // MAINWINDOW_H
