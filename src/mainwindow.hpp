#pragma once

#include "RenderArea.hpp"
#include <QMainWindow>
#include <QScopedPointer>
#include <src/Simulation/MpkSimulator.hpp>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

  ~MainWindow() override;
  std::shared_ptr<MPKWorld> mpkWorld = nullptr;
  std::shared_ptr<MpkSimulator> mpkSimulator = nullptr;

private:
  QScopedPointer<Ui::MainWindow> ui;
  QScopedPointer<RenderArea> renderArea;
};
