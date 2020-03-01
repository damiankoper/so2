#pragma once
#include "DrawerInterface.hpp"
#include "../MPK/Relation.hpp"
#include <QPainter>
class RelationDrawer : public DrawerInterface
{
public:
    void setRelation(Relation *relation);
    void setNth(int nth = 0);
    void draw(QPainter &painter) override;

private:
    Relation *relation = nullptr;

    // Nth defines offset according to other relations in case of overlappin
    int nth = 0;

    int RELATION_SIZE = 25;
    int RELATION_STROKE = 8;
};