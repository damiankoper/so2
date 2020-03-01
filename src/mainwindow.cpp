#include "mainwindow.hpp"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), renderArea(new RenderArea(this))
{
    MPKWorld *world = new MPKWorld();
    Stop *stop = new Stop(Vector2i(300, 300), "Kościuszki");
    Stop *stop_another = new Stop(Vector2i(500, 400), "Komuny Paryskiej");
    Stop *stop_another_other = new Stop(Vector2i(720, 300), "Plac Wróblewskiego");
    Stop *stop_another_other_hehe = new Stop(Vector2i(820, 200), "Most Grunwaldzki");
    Stop *stop_another_other_hehe_hihi = new Stop(Vector2i(299, 100), "Plac Grunwaldzki");
    world->stops.push_back(stop);
    world->stops.push_back(stop_another);
    world->stops.push_back(stop_another_other);
    world->stops.push_back(stop_another_other_hehe);
    world->stops.push_back(stop_another_other_hehe_hihi);

    Relation *relation = new Relation("16");
    relation->addStop(stop);
    relation->addStop(stop_another);
    relation->addStop(stop_another_other);
    relation->addStop(stop_another_other_hehe);
    relation->addStop(stop_another_other_hehe_hihi);
    relation->addStop(stop, false); //cycle

    Relation *relation2 = new Relation("OL", "blue");
    relation2->addStop(stop);
    relation2->addStop(stop_another);
    relation2->addStop(stop_another_other);
    relation2->addStop(stop, false);

    Relation *relation3 = new Relation("OP", "green");
    relation3->addStop(stop_another);
    relation3->addStop(stop_another_other);
    relation3->addStop(stop_another, false);

    world->relations.push_back(relation);
    world->relations.push_back(relation2);
    world->relations.push_back(relation3);

    renderArea->setMPKWorld(world);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
}
