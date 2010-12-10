#ifndef LOGICSIMPLIFIER_H
#define LOGICSIMPLIFIER_H

#include <QString>
#include <QList>
#include <QStringList>

class LogicSimplifier
{
public:
    LogicSimplifier();
    void simplifyEquation(QString equation);
    static QString guineMcCluskeySimplification(QList<uint> primeImplicant, QStringList inputName = QStringList()); ///@param primeImplicant list of 1 and X implicants combined
    static unsigned int greyCodeGenerator(unsigned pos);
    static QString dec2bin(uint input, unsigned length=0);
private:
    void stringToInternal(QString equation);
};

#endif // LOGICSIMPLIFIER_H
