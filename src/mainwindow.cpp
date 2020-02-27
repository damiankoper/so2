#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QTextLine>
#include <QLabel>
#include <QPoint>
#include <QPainter>
#include <QPen>
#include "MPK/Stop.hpp"
#include "Geometry/Vector2i.hpp"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    Stop *stop = new Stop(Vector2i(100, 100), "16", this);
    stop->move(200, 200);

    ui->setupUi(this);
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    static const QPointF points[3] = {
        QPointF(10.0, 80.0),
        QPointF(20.0, 10.0),
        QPointF(80.0, 30.0),
    };

    QPainter painter(this);
    QPen pen;
    pen.setWidth(5);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.drawPolyline(points, 3);
}

MainWindow::~MainWindow()
{
}
