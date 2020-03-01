#include "RelationDrawer.hpp"
#include <QString>
#include <QColor>
void RelationDrawer::setRelation(Relation *relation)
{
    this->relation = relation;
}

void RelationDrawer::setNth(int nth)
{
    this->nth = nth;
}

void RelationDrawer::draw(QPainter &painter)
{
    // W sumie useless jest Vector2i jak jest QPoint
    std::vector<QPoint> points = std::vector<QPoint>();
    int xMin = 720;
    int xMax = 0;
    for (auto &&point : relation->getPoints())
    {
        xMin = std::min(xMin, point.x);
        xMax = std::max(xMax, point.x);
    }
    int center = (xMax + xMin) / 2;

    for (auto &&point : relation->getPoints())
    {
        if (point.x >= center)
        {
            point.x += nth * 8;
        }
        else
        {
            point.x -= nth * 8;
        }
        points.push_back(QPoint(point.x, point.y + nth * 15));
    }

    QPen pen(QColor(relation->color.c_str()), RELATION_STROKE, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
    painter.setPen(pen);

    painter.drawPolyline(points.data(), points.size());
}