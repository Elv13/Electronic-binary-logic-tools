#ifndef GATEBASE_H
#define GATEBASE_H

#include <QGraphicsItemGroup>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsLineItem>
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
    void addConnectedLine(QGraphicsLineItem* aLine);

protected:
    virtual QPoint addInput(bool invert = false) {}
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    QColor gateColor;
    QPen gatePen;
    QPen gatePenHighlight;
    QList<ParentGates> parent;
    QList<QGraphicsLineItem*> connectedLines;
    QList<QAbstractGraphicsShapeItem*> content;
private:
    virtual void createGate(uint inputCount) {}

};

#endif // GATEBASE_H
