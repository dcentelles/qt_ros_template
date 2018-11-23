#include <QDebug>
#include <QTime>
#include <hmi/logger.h>
#include <hmi/mainwindow.h>
#include <qtimer.h>
#include <ui_mainwindow.h>

MainWindow::MainWindow(int argc, char **argv, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->outputPlainTextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::printMessage(const QString &notif, const QString &colorName) {
  QTime time = QTime::currentTime();
  QString msg = QString("<font color=\"%4\">%2:&nbsp;</font>"
                        "<font color=\"%1\">%3 </font>")
                    .arg(colorName, time.toString("HH:mm:ss"), notif, "brown");
  ui->outputPlainTextEdit->appendHtml(msg);
}

void MainWindow::newLog(const Log::LogLevel &level, const QString &msg) {
  switch (level) {
  case (Log::DebugLv): {
    printMessage(msg, "green");
    break;
  }
  case (Log::InfoLv): {
    printMessage(msg, "blue");
    break;
  }
  case (Log::WarnLv): {
    printMessage(msg, "yellow");
    break;
  }
  case (Log::ErrorLv): {
    printMessage(msg, "red");
    break;
  }
  case (Log::FatalLv): {
    printMessage(msg, "red");
    break;
  }
  }
}
void MainWindow::on_reverseButton_pressed() { Log::Debug("Reverse"); }

void MainWindow::on_forwardButton_pressed() { Log::Debug("Forward"); }

void MainWindow::on_rightButton_pressed() { Log::Debug("Right"); }

void MainWindow::on_turnRightButton_pressed() { Log::Debug("Turn Right"); }

void MainWindow::on_turnLeftButton_pressed() { Log::Debug("Turn Left"); }

void MainWindow::on_leftButton_pressed() { Log::Debug("Left"); }

void MainWindow::on_forwardButton_released() { Log::Debug("Release Forward"); }

void MainWindow::on_reverseButton_released() { Log::Debug("Release Reverse"); }

void MainWindow::on_rightButton_released() { Log::Debug("Release Right"); }

void MainWindow::on_turnRightButton_released() {
  Log::Debug("Release Turn Right");
}

void MainWindow::on_turnLeftButton_released() {
  Log::Debug("Release Turn Left");
}

void MainWindow::on_leftButton_released() { Log::Debug("Release Left"); }
