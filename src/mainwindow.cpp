#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      renderArea(new RenderArea(this)) {
  auto *world = new MPKWorld();

  Stop *stopKosciuszki = new Stop(Vector2i(300, 300), "Kościuszki");
  Stop *stopKomunyParyskiej = new Stop(Vector2i(500, 400), "Komuny Paryskiej");
  Stop *stopPlacWroblewskiego = new Stop(Vector2i(720, 300), "Plac Wróblewskiego");
  Stop *stopMostGrunwaldzki =
      new Stop(Vector2i(820, 200), "Most Grunwaldzki");
  Stop *stopPlacGrunwaldzki =
      new Stop(Vector2i(299, 100), "Plac Grunwaldzki");
  Stop *stopNowowiejska =
      new Stop(Vector2i(800, 600), "Nowowiejska");
  Stop *stopPlacDominikanski =
      new Stop(Vector2i(200, 550), "Plac Dominikański");
  world->stops.push_back(stopKosciuszki);
  world->stops.push_back(stopKomunyParyskiej);
  world->stops.push_back(stopPlacWroblewskiego);
  world->stops.push_back(stopMostGrunwaldzki);
  world->stops.push_back(stopPlacGrunwaldzki);
  world->stops.push_back(stopNowowiejska);
  world->stops.push_back(stopPlacDominikanski);

  auto *relation = new Relation("16");
  relation->addStop(stopKosciuszki);
  relation->addStop(stopKomunyParyskiej);
  relation->addStop(stopPlacWroblewskiego);
  relation->addStop(stopMostGrunwaldzki);
  relation->addStop(stopPlacGrunwaldzki);
  relation->addStop(stopKosciuszki, false); // cycle

  auto *relation2 = new Relation("OL", "blue");
  relation2->addStop(stopKosciuszki);
  relation2->addStop(stopKomunyParyskiej);
  relation2->addStop(stopPlacWroblewskiego);
  relation2->addStop(stopKosciuszki, false);

  auto *relation3 = new Relation("OP", "green");
  relation3->addStop(stopKomunyParyskiej);
  relation3->addStop(stopPlacWroblewskiego);
  relation3->addStop(stopKomunyParyskiej, false);

  auto *relation4 = new Relation("5", "magenta");
  relation4->addStop(stopKomunyParyskiej);
  relation4->addStop(stopPlacWroblewskiego);
  relation4->addStop(stopNowowiejska);
  relation4->addStop(stopKomunyParyskiej, false);

  auto *relation5 = new Relation("17", "cyan");
  relation5->addStop(stopKomunyParyskiej);
  relation5->addStop(stopPlacWroblewskiego);
  relation5->addStop(stopNowowiejska);
  relation5->addStop(stopPlacDominikanski);
  relation5->addStop(stopKomunyParyskiej, false);

  world->relations.push_back(relation);
  world->relations.push_back(relation2);
  world->relations.push_back(relation3);
  world->relations.push_back(relation4);
  world->relations.push_back(relation5);

  /**
   * Dynamic from here
   */
  auto *v1 = new Vehicle();
  v1->position = 100;
  relation->vehicles.push_back(v1);

  renderArea->setMPKWorld(world);
  ui->setupUi(this);

}

MainWindow::~MainWindow() = default;
