#include "MPK/Passenger.hpp"
#include "MPK/Stop.hpp"
#include "mainwindow.hpp"
#include <QApplication>
int main(int argc, char *argv[]) {
  srand(time(nullptr));
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.setFixedSize(1280, 720);
  mainWindow.show();
  return QApplication::exec();
}
