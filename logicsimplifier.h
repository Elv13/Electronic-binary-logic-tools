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
private:
    void stringToInternal(QString equation);
};

#endif // LOGICSIMPLIFIER_H
