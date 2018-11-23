#include <hmi/logger.h>

namespace hmi {

static Log logger;
std::mutex Log::locker;

Log::Log() {}

Log &Log::Create() { return logger; }

void Log::Info(const QString &msg) { log(LogLevel::InfoLv, msg); }
void Log::Debug(const QString &msg) { log(LogLevel::DebugLv, msg); }
void Log::Error(const QString &msg) { log(LogLevel::ErrorLv, msg); }
void Log::Warn(const QString &msg) { log(LogLevel::WarnLv, msg); }

void Log::log(const LogLevel &level, const QString &msg) {
  locker.lock();
  if (!ros::master::check()) {
    QString _msg = "(not connected to ROS master) " + msg;
    Q_EMIT logger.newLog(ErrorLv, _msg);
    locker.unlock();
    return;
  }
  ROS_DEBUG_STREAM(msg.toStdString());

  Q_EMIT logger.newLog(level,
                       msg); // used to readjust the scrollbar
  locker.unlock();
}

} // namespace hmi
