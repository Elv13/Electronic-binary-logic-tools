#ifndef GATEBASE_H
#define GATEBASE_H

#include <QGraphicsItemGroup>
#include <QColor>
#include <QPen>
#include <QObject>

class GateBase;

struct ParentGates {
    GateBase* gate;
    bool invert;
    uint index;
};

class GateBase : public QGraphicsItemGroup
{
public:
    explicit GateBase(QObject *parent = 0);
    virtual QPoint outputRelCoord() {}
    virtual QString getEquation() {}
    QPoint addParentGate(GateBase* gate, bool invert);

protected:
    virtual QPoint addInput(bool invert = false) {}
    QColor gateColor;
    QPen gatePen;
    QList<ParentGates> parent;
private:
    virtual void createGate(uint inputCount) {}

};

#endif // GATEBASE_H
