#pragma once
#include "../MPK/Relation.hpp"
#include "DrawerInterface.hpp"
#include <QPainter>
class RelationDrawer : public DrawerInterface {
public:
  void setRelation(Relation *relation);
  void draw(QPainter &painter) override;

private:
  Relation *relation = nullptr;

  int RELATION_SIZE = 25;
  int RELATION_STROKE = 8;
};