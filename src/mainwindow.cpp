#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <src/Simulation/MpkSimulator.hpp>
#include <src/Simulation/StopSimulator.hpp>
#include <src/Simulation/VehicleSimulator.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      renderArea(new RenderArea(this)) {
  this->mpkWorld = std::make_shared<MPKWorld>();

  Stop *stopKosciuszki = new Stop(Vector2i(300, 300), "Kościuszki");
  Stop *stopKomunyParyskiej = new Stop(Vector2i(500, 400), "Komuny Paryskiej");
  Stop *stopPlacWroblewskiego =
      new Stop(Vector2i(720, 300), "Plac Wróblewskiego");
  Stop *stopMostGrunwaldzki = new Stop(Vector2i(820, 200), "Most Grunwaldzki");
  Stop *stopPlacGrunwaldzki = new Stop(Vector2i(299, 100), "Plac Grunwaldzki");
  Stop *stopNowowiejska = new Stop(Vector2i(800, 600), "Nowowiejska");
  Stop *stopPlacDominikanski =
      new Stop(Vector2i(200, 550), "Plac Dominikański");
  Stop *stopHubska = new Stop(Vector2i(1000, 400), "Hubska");

  std::vector<Stop *> allStops{stopKosciuszki,        stopKomunyParyskiej,
                               stopPlacWroblewskiego, stopMostGrunwaldzki,
                               stopPlacGrunwaldzki,   stopNowowiejska,
                               stopPlacDominikanski,  stopHubska};
  for (auto stop : allStops) {
    this->mpkWorld->stops.push_back(stop);
  }

  auto *relation16 = new Relation("16");
  relation16->addStop(stopKosciuszki);
  relation16->addStop(stopKomunyParyskiej);
  relation16->addStop(stopPlacWroblewskiego);
  relation16->addStop(stopMostGrunwaldzki);
  relation16->addStop(stopPlacGrunwaldzki);
  relation16->addStop(stopKosciuszki, false); // cycle

  auto *relation0L = new Relation("OL", "blue");
  relation0L->addStop(stopKosciuszki);
  relation0L->addStop(stopKomunyParyskiej);
  relation0L->addStop(stopPlacWroblewskiego);
  relation0L->addStop(stopKosciuszki, false);

  auto *relation0P = new Relation("OP", "green");
  relation0P->addStop(stopKomunyParyskiej);
  relation0P->addStop(stopPlacWroblewskiego);
  relation0P->addStop(stopKomunyParyskiej, false);

  auto *relation5 = new Relation("5", "magenta");
  relation5->addStop(stopKomunyParyskiej);
  relation5->addStop(stopPlacWroblewskiego);
  relation5->addStop(stopHubska);
  relation5->addStop(stopNowowiejska);
  relation5->addStop(stopKomunyParyskiej, false);

  auto *relation17 = new Relation("17", "cyan");
  relation17->addStop(stopKomunyParyskiej);
  relation17->addStop(stopPlacWroblewskiego);
  relation17->addStop(stopNowowiejska);
  relation17->addStop(stopPlacDominikanski);
  relation17->addStop(stopKomunyParyskiej, false);

  std::vector<Relation *> allRelations{relation16, relation0L, relation0P,
                                       relation5, relation17};

  for (auto relation : allRelations) {
    this->mpkWorld->relations.push_back(relation);
  }

  /**
   * Dynamic from here
   */
  auto addViehcles = [](Relation *relation, int count) {
    int distance = 0;
    for (size_t i = 0; i < count; i++) {
      auto *v = new Vehicle();
      v->distance = distance;
      relation->vehicles.push_back(v);
      distance += 300;
    }
  };

  addViehcles(relation16, 6);
  addViehcles(relation17, 6);
  addViehcles(relation0P, 2);
  addViehcles(relation0L, 6);
  addViehcles(relation5, 3);

  this->mpkSimulator = std::make_shared<MpkSimulator>(allRelations);
  this->mpkSimulator->startSimulation();
  renderArea->setMPKWorld(this->mpkWorld.get());
  ui->setupUi(this);
}

MainWindow::~MainWindow() {}
