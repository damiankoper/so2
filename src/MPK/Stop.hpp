#include "../Geometry/Vector2i.hpp"
#include <QWidget>
#include <QLabel>
#include <QPoint>
#include <QPainter>
#include <QPen>
class Stop : public QWidget
{
    Q_OBJECT

public:
    Stop(Vector2i position, std::string name, QWidget *parent) : position(position), name(name), QWidget(parent)
    {
        this->setFixedSize(300, 300);
        QLabel *text = new QLabel("Dupka", this);
    }

    Stop(const Stop &stop) : Stop(stop.position, stop.name, stop.parentWidget()) {}

    Stop &operator=(const Stop &stop);

    ~Stop(){};

    std::string name;
    Vector2i position;

    QSize sizeHint() const
    {
        return QSize(200, 200);
    }

    QSize minimumSizeHint() const
    {
        return QSize(200, 200);
    }

protected:
    void paintEvent(QPaintEvent *event)
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
};