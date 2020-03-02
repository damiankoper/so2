#include "RelationDrawer.hpp"
#include <QString>
#include <QColor>
void RelationDrawer::setRelation(Relation *relation)
{
    this->relation = relation;
}


void RelationDrawer::draw(QPainter &painter)
{
    // W sumie useless jest Vector2i jak jest QPoint
    std::vector<QPoint> points = std::vector<QPoint>();

    for (auto &&point : relation->getPoints())
    {
        points.push_back(QPoint(point.x, point.y));
    }

    QPen pen(QColor(relation->color.c_str()), RELATION_STROKE, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    painter.setPen(pen);

    painter.drawPolyline(points.data(), points.size());
}