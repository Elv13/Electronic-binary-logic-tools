#include "circuitline.h"
#include <QPalette>

CircuitLine::CircuitLine(QLine line, GateBase* gate1, GateBase* gate2, QGraphicsItemGroup* parent) : QGraphicsLineItem(line,parent)
{
    QPalette aPalette;

    linePen.setWidth(2);
    QColor lineColor = aPalette.text().color();
    lineColor.setAlpha(100);
    linePen.setColor(lineColor);

    m_gate1 = gate1;
    m_gate2 = gate2;

    setPen(linePen);
}
