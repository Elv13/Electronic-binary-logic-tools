#ifndef GATEBASE_H
#define GATEBASE_H

#include <QGraphicsItemGroup>
#include <QColor>
#include <QPen>
#include <QObject>

class GateBase : public QGraphicsItemGroup
{
public:
    explicit GateBase(QObject *parent = 0);
    virtual QPoint outputRelCoord() {}
    virtual QPoint addInput(bool invert = false) {}

protected:
    QColor gateColor;
    QPen gatePen;
private:
    virtual void createGate(uint inputCount) {}

};

#endif // GATEBASE_H
