#include <QApplication>

int main(int argc, char **argv) {
	QApplication app(argc, argv);

	qDebug() << "Wireframe viewer starting";
	return app.exec();
}
