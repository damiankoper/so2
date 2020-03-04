#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <src/Simulation/MpkSimulator.hpp>
#include <src/Simulation/StopSimulator.hpp>
#include <src/Simulation/VehicleSimulator.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      renderArea(new RenderArea(this)) {
  this->mpkWorld = std::make_shared<MPKWorld>();
  this->mpkSimulator = std::make_shared<MpkSimulator>();

  Stop *stopKosciuszki = new Stop(Vector2i(300, 300), "Kościuszki");
  Stop *stopKomunyParyskiej = new Stop(Vector2i(500, 400), "Komuny Paryskiej");
  Stop *stopPlacWroblewskiego =
      new Stop(Vector2i(720, 300), "Plac Wróblewskiego");
  Stop *stopMostGrunwaldzki = new Stop(Vector2i(820, 200), "Most Grunwaldzki");
  Stop *stopPlacGrunwaldzki = new Stop(Vector2i(299, 100), "Plac Grunwaldzki");
  Stop *stopNowowiejska = new Stop(Vector2i(800, 600), "Nowowiejska");
  Stop *stopPlacDominikanski =
      new Stop(Vector2i(200, 550), "Plac Dominikański");

  std::vector<Stop *> allStops{stopKosciuszki,        stopKomunyParyskiej,
                               stopPlacWroblewskiego, stopMostGrunwaldzki,
                               stopPlacGrunwaldzki,   stopNowowiejska,
                               stopPlacDominikanski};
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
//    this->mpkSimulator->createStopSimulatorsFromRelation();
  }

  /**
   * Dynamic from here
   */
  auto *v1 = new Vehicle();
  auto *v2 = new Vehicle();
  auto *v3 = new Vehicle();
  auto *v4 = new Vehicle();
  auto *v5 = new Vehicle();
  relation0L->vehicles.push_back(v1);
  relation0P->vehicles.push_back(v2);
  relation16->vehicles.push_back(v3);
  relation17->vehicles.push_back(v4);
  relation5->vehicles.push_back(v5);

  renderArea->setMPKWorld(this->mpkWorld.get());
  ui->setupUi(this);
  this->mpkSimulator->startSimulation();
}

MainWindow::~MainWindow() = default;
