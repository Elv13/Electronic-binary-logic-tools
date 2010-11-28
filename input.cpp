#include "input.h"
#include <QGraphicsSimpleTextItem>
#include <QPoint>

Input::Input(QString text)
{
    QPainterPath inputPath;
    inputPath.lineTo(35,0);
    inputPath.lineTo(50,15);
    inputPath.lineTo(35,30);
    inputPath.lineTo(0,30);
    inputPath.lineTo(0,0);
    QGraphicsPathItem* inputItem = new QGraphicsPathItem();
    inputItem->setPath(inputPath);
    inputItem->setPen(gatePen);
    inputItem->setBrush(gateColor);
    inputItem->setPos(0,10);
    addToGroup(inputItem);

    QGraphicsSimpleTextItem* inputName = new QGraphicsSimpleTextItem;
    inputName->setPos(5,15);
    inputName->setText(text);
    addToGroup(inputName);
}

void Input::createGate(uint inputCount)
{

}

QPoint Input::outputRelCoord()
{
    return QPoint(50,25);
}

QPoint Input::addInput(bool invert)
{

}
