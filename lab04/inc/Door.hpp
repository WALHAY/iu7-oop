#include <QObject>

class Door : public QObject {
  Q_OBJECT;

public:
  explicit Door(QObject *parent = nullptr);

signals:

public slots:
};
