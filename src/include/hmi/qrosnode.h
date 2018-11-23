#ifndef QROSNODE_H
#define QROSNODE_H
#include "std_msgs/String.h"
#include <QStringListModel>
#include <QThread>
#include <hmi/common.h>
#include <ros/network.h>
#include <ros/ros.h>

namespace hmi {

class QROSNode : public QThread {
  Q_OBJECT
public:
  QROSNode(int argc, char **argv);
  virtual ~QROSNode();
  bool init();
  bool init(const std::string &master_url, const std::string &host_url);
  void run();
public slots:
  void controlsUpdate(const ButtonsStatus &);
signals:
  void rosShutdown();

private:
  void CreateROSCommunications();
  int init_argc;
  char **init_argv;
};
} // namespace hmi
#endif // QROSNODE_H
