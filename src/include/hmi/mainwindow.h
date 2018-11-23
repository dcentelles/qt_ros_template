#ifndef HMI_MAINWINDOW_H
#define HMI_MAINWINDOW_H

#include <QMainWindow>
#include <hmi/logger.h>
#include <hmi/qrosnode.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(int argc, char **argv, QWidget *parent = 0);
  ~MainWindow();

public slots:
  void newLog(const Log::LogLevel &, const QString &);

private slots:
  void on_reverseButton_pressed();

  void on_forwardButton_pressed();

  void on_rightButton_pressed();

  void on_turnRightButton_pressed();

  void on_turnLeftButton_pressed();

  void on_leftButton_pressed();

  void on_forwardButton_released();

  void on_reverseButton_released();

  void on_rightButton_released();

  void on_turnRightButton_released();

  void on_turnLeftButton_released();

  void on_leftButton_released();

private:
  Ui::MainWindow *ui;

  void printMessage(const QString &notif, const QString &colorName);
};
#endif // HMI_MAINWINDOW_H
