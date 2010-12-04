#ifndef CIRCUITLINE_H
#define CIRCUITLINE_H

#include <QObject>
#include <QGraphicsLineItem>
#include <QGraphicsItemGroup>
#include <QPen>
#include "gatebase.h"

class CircuitLine: public QGraphicsLineItem
{
public:
    explicit CircuitLine(QLine line, GateBase* gate1, GateBase* gate2, QGraphicsItemGroup* parent);

    GateBase* m_gate1;
    GateBase* m_gate2;
private:
    QPen linePen;

signals:

public slots:

};

#endif // CIRCUITLINE_H
