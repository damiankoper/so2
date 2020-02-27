#include <QApplication>
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.setFixedSize(1280, 720);
    mainWindow.show();
    return app.exec();
}
