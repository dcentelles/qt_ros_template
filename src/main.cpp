#include <QApplication>
#include <hmi/logger.h>
#include <hmi/mainwindow.h>
#include <hmi/qrosnode.h>

using namespace hmi;

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

  QObject::connect(&w, SIGNAL(controlsUpdate(const ButtonsStatus &)), &rosNode,
                   SLOT(controlsUpdate(const ButtonsStatus &)));

  rosNode.init();
  w.show();

  return a.exec();
}
