#include "andgate.h"

#include <QGraphicsEllipseItem>


AndGate::AndGate(QObject *parent, uint inputCount):
    inputCount(0)
{
    createGate(inputCount);
}

void AndGate::createGate(uint inputCount)
{
    QPainterPath andPath;
    andPath.arcTo(0,0,50,50,90,-180);
    andPath.lineTo(0,50);
    andPath.lineTo(0,0);
    QGraphicsPathItem* andGate = new QGraphicsPathItem();
    andGate->setPath(andPath);
    andGate->setPen(gatePen);
    andGate->setBrush(gateColor);

    addToGroup(andGate);
    content << andGate;
}

QPoint AndGate::outputRelCoord()
{
    return QPoint(50,25);
}

QPoint AndGate::addInput(bool invert)
{
    if (invert) {
        QGraphicsEllipseItem* anInverter = new QGraphicsEllipseItem(this);
        anInverter->setRect(0,0,10,10);
        anInverter->setPos(0,10*inputCount);
        anInverter->setPen(gatePen);
        anInverter->setBrush(gateColor);
        addToGroup(anInverter);
        content << anInverter;
    }
    inputCount++;
    return QPoint(0,(inputCount-1)*10);
}

QString AndGate::getEquation() {

}
