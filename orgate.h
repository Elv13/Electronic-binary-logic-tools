#ifndef ORGATE_H
#define ORGATE_H

#include <QGraphicsItemGroup>
#include "gatebase.h"
#include <QGraphicsPathItem>
#include <QPainterPath>

class OrGate : public GateBase//, QObject
{
    //Q_OBJECT
public:
    explicit OrGate(QObject *parent = 0, uint inputCount = 2);
    virtual QPoint outputRelCoord();
    virtual QPoint addInput(bool invert = false);
    virtual QString getEquation();
private:
    virtual void createGate(uint inputCount);
    int inputCount;

signals:

public slots:

};

#endif // ORGATE_H
