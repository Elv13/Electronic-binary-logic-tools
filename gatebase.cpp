#include "gatebase.h"
#include <QDebug>

GateBase::GateBase(QObject *parent)
{
    gateColor.setNamedColor("#7799FF");
    gateColor.setAlpha(155);

    gatePen.setColor("#0000FF");
    gatePen.setWidth(2);

    gatePenHighlight.setColor("#FF0000");
}

QPoint GateBase::addParentGate(GateBase* gate, bool invert)
{
    parent << ParentGates({gate,invert,0});
    return addInput(invert);
}

void GateBase::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    qDebug() << "I am here";
    foreach (QGraphicsLineItem* aLine, connectedLines) {
        aLine->setPen(gatePenHighlight);
    }
    foreach (QAbstractGraphicsShapeItem* item, content) {
        item->setPen(gatePenHighlight);
    }
}

void GateBase::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    qDebug() << "I am here2";
    foreach (QGraphicsLineItem* aLine, connectedLines) {
        aLine->setPen(gatePen);
    }
    foreach (QAbstractGraphicsShapeItem* item, content) {
        item->setPen(gatePen);
    }
}

void GateBase::addConnectedLine(QGraphicsLineItem* aLine)
{
    connectedLines << aLine;
}
