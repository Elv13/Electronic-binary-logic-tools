#include "gatebase.h"

GateBase::GateBase(QObject *parent)
{
    gateColor.setNamedColor("#7799FF");
    gateColor.setAlpha(155);


    gatePen.setColor("#0000FF");
    gatePen.setWidth(2);
}
