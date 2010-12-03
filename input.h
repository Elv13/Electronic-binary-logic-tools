#ifndef INPUT_H
#define INPUT_H

#include "gatebase.h"

class Input : public GateBase
{
public:
    Input(QString text);
    virtual QPoint outputRelCoord();
    virtual QPoint addInput(bool invert = false);
private:
    virtual void createGate(uint inputCount);
};

#endif // INPUT_H
