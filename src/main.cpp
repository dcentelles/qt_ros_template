#include <QApplication>
#include <hmi/logger.h>
#include <hmi/mainwindow.h>
#include <hmi/qrosnode.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // Logging
  Log &log = Log::Create();

  // ROS interface
  QROSNode rosNode(argc, argv);

  // UI
  MainWindow w(argc, argv);

  QObject::connect(&log, SIGNAL(newLog(const Log::LogLevel &, const QString &)),
                   &w, SLOT(newLog(const Log::LogLevel &, const QString &)));

  rosNode.init();
  w.show();

  return a.exec();
}
