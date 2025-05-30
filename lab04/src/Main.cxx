#include "../inc/Door.hpp"
#include <QDebug>
#include <QThread>
#include <QApplication>

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  Door door{};
	door.opening();

  return app.exec(); 
}
