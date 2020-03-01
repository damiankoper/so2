#include "mainwindow.hpp"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), renderArea(new RenderArea(this))
{
    MPKWorld *world = new MPKWorld();
    Stop *stop = new Stop(Vector2i(300, 300), "Kościuszki");
    Stop *stop_another = new Stop(Vector2i(500, 400), "Komuny Paryskiej");
    Stop *stop_another_other = new Stop(Vector2i(500, 200), "Plac Wróblewskiego");
    world->stops.push_back(stop);
    world->stops.push_back(stop_another);
    world->stops.push_back(stop_another_other);

    Relation *relation = new Relation("16");
    relation->stops.push_back(stop);
    relation->stops.push_back(stop_another);
    relation->stops.push_back(stop_another_other);
    relation->stops.push_back(stop); //cycle
    world->relations.push_back(relation);

    renderArea->setMPKWorld(world);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
}
