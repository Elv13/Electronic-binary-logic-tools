#include "logicsimplifier.h"

#include <QHash>
#include <QDebug>

/*struct mergedTerms {
   uint filter;
   QList<int> terms;
   uint filteredOneCount;
}*/

LogicSimplifier::LogicSimplifier()
{

}

//Generate a bit sequence where "i" are next to each other (Gray code)
unsigned int LogicSimplifier::greyCodeGenerator(unsigned pos)
{
  return (pos>>1) ^ pos;
}

QString LogicSimplifier::dec2bin(uint input, unsigned length)
{
    QString output;
    for (int i=0;i< (length?length+1:(sizeof(int)*8));i++)
        output = 0x30+((input>>i)&0x01) + output; //Push front (Bin to ascii)
    return output;
}

/*QList<int> customSort(QHash<int,mergedTerms> &merged)
{
    QList<int> toReturn;

    return toReturn;
}*/

QString LogicSimplifier::guineMcCluskeySimplification(QList<uint> primeImplicant, QStringList inputName)
{
    /*if (varCount == -1) {
        foreach (int val, primeImplicant) {
            //TOOD
        }
    }*/
//Faire une fonction sort 

    //Step 1: Group them by the number of 1
    /*QHash<int, QList<int> > groups;
    foreach (int val,primeImplicant) {
        int numOfOne = 0;
        for (int i=1;i<=(1<<inputName.count());i<<1) {
            numOfOne += val&i;
        }
        groups[numOfOne] << val;
        merged[val].filter = 0;
        merged[val].filteredOneCount = val;
    }

    QList<int> countIndex = customSort(QHash<int,mergedTerms> &merged);

    //Step 2: Compare with (number of 1) + 1, output pairs
    QHash<int,mergedTerms> merged;
    //Par recursif?
    for (int i=1;i<inputName.count()-1;i++) {
        foreach (int val, groups[i]) {
            foreach (int val2, groups[i+1]){
//Don't forgot to remove the different bit before the next loop
                merged[val].filter |= val ^ val2;
                merged[val].terms << val2;
            }
        }
    }*/

    //Step 3: Check for other passes

    //Step 4: I am not even sure about this one

}
