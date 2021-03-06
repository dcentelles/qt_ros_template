#include <QDebug>
#include <QImage>
#include <hmi/logger.h>
#include <hmi/qrosnode.h>
#include <hmi_msgs/Controls.h>
#include <ros/publisher.h>
#include <thread>

namespace hmi {
QROSNode::QROSNode(int argc, char **argv) : init_argc(argc), init_argv(argv) {
  init();
}

QROSNode::~QROSNode() {
  if (ros::isStarted()) {
    ros::shutdown(); // explicitly needed since we use ros::start();
    ros::waitForShutdown();
  }
  wait();
}

bool QROSNode::init() {
  ros::init(init_argc, init_argv, "hmi");
  if (!ros::master::check()) {
    return false;
  }
  ros::start(); // explicitly needed since our nodehandle is going out of scope.

  // Add your ros communications here.
  CreateROSCommunications();

  start();
  return true;
}
bool QROSNode::init(const std::string &master_url,
                    const std::string &host_url) {
  std::map<std::string, std::string> remappings;
  remappings["__master"] = master_url;
  remappings["__hostname"] = host_url;
  ros::init(remappings, "hmi");
  if (!ros::master::check()) {
    return false;
  }
  ros::start(); // explicitly needed since our nodehandle is going out of scope.

  CreateROSCommunications();

  start();
  return true;
}

void QROSNode::CreateROSCommunications() {
  ros::NodeHandle nh("~");
  controlsPublisher = nh.advertise<hmi_msgs::Controls>("controls", 1);
}

void QROSNode::run() {
  ros::Rate loop_rate(10);
  int count = 0;
  while (ros::ok()) {

    // Do something
    //...

    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
  Log::Info("ROS shutdown, proceeding to close the gui.");
  Q_EMIT
  rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

void QROSNode::publishControls() {
  hmi_msgs::Controls msg;
  msg.down = controls.down;
  msg.up = controls.up;
  msg.forward = controls.forward;
  msg.reverse = controls.reverse;
  msg.left = controls.left;
  msg.right = controls.right;
  msg.turn_left = controls.tleft;
  msg.turn_right = controls.tright;
  controlsPublisher.publish(msg);
}

void QROSNode::controlsUpdate(const ButtonsStatus &bs) {
  controls = bs;
  publishControls();
}
} // namespace hmi
