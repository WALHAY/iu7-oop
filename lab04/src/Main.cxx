#include "Cabin.hpp"
#include "MainWindow.hpp"
#include <QApplication>
#include <QDebug>
#include <QThread>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  Cabin cabin;
  cabin.move();

  MainWindow window;
  window.show();

  return app.exec();
}
