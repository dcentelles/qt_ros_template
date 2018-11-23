#ifndef HMI_LOGGER_H_
#define HMI_LOGGER_H_
#include <QObject>
#include <mutex>
#include <ros/network.h>
#include <ros/ros.h>

class Log : public QObject {
  Q_OBJECT

public:
  enum LogLevel { DebugLv, InfoLv, WarnLv, ErrorLv, FatalLv };
  Log();
  static Log &Create();

  static void Info(const QString &msg);
  static void Debug(const QString &msg);
  static void Error(const QString &msg);
  static void Fatal(const QString &msg);
  static void Warn(const QString &msg);
signals:
  void newLog(const Log::LogLevel &, const QString &);

private:
  static void log(const LogLevel &level, const QString &msg);
  static std::mutex locker;
};
#endif // HMI_LOGGER_H_
