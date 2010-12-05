#ifndef INPUT_H
#define INPUT_H

#include "gatebase.h"

class Input : public GateBase
{
public:
    Input(QString text);
    virtual QPoint outputRelCoord();
    virtual QPoint addInput(bool invert = false);
    virtual QString getEquation();
private:
    virtual void createGate(uint inputCount);
    QString text;
};

#endif // INPUT_H
