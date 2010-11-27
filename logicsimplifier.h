#ifndef LOGICSIMPLIFIER_H
#define LOGICSIMPLIFIER_H

#include <QString>

class LogicSimplifier
{
public:
    LogicSimplifier();
    void simplifyEquation(QString equation);
private:
    void stringToInternal(QString equation);
};

#endif // LOGICSIMPLIFIER_H
