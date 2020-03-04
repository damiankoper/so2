#pragma once

#include <QMainWindow>
#include <QScopedPointer>
#include "RenderArea.hpp"
namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    QScopedPointer<Ui::MainWindow> ui;
    QScopedPointer<RenderArea> renderArea;
};
