#ifndef ANDGATE_H
#define ANDGATE_H

#include <QGraphicsPathItem>
#include <QPainterPath>
#include "gatebase.h"

class AndGate : public GateBase
{
public:
    AndGate(QObject *parent = 0, uint inputCount = 2);
    virtual QPoint outputRelCoord();
    virtual QPoint addInput(bool invert = false);

private:
    virtual void createGate(uint inputCount);
    int inputCount;
};

#endif // ANDGATE_H
