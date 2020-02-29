#include "mainwindow.hpp"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), renderArea(new RenderArea(this))
{
    MPKWorld *world = new MPKWorld();
    Stop *stop = new Stop(Vector2i(300, 300), "Kościuszki");
    Stop *stop_another = new Stop(Vector2i(500, 400), "Komuny Paryskiej");
    world->stops.push_back(stop);
    world->stops.push_back(stop_another);

    renderArea->setMPKWorld(world);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
}
