#include "orgate.h"

OrGate::OrGate(QObject *parent, uint inputCount):
    inputCount(0)
{
    createGate(inputCount);
}

void OrGate::createGate(uint inputCount)
{
    QPainterPath orPath;
    orPath.arcTo(0,0,50,50,90,-180);
    orPath.arcTo(-10,50,25,-50,90,-180);
    QGraphicsPathItem* orGate = new QGraphicsPathItem();
    orGate->setPath(orPath);
    orGate->setPen(gatePen);
    orGate->setBrush(gateColor);
    addToGroup(orGate);
    content << orGate;
}

QPoint OrGate::outputRelCoord()
{
    return QPoint(50,25);
}

QPoint OrGate::addInput(bool invert)
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

QString OrGate::getEquation()
{

}
