#include "logicsimplifier.h"

#include <QHash>

struct mergedTerms {
   uint filter = 0;
   QList<int> terms;
   uint filteredOneCount;
}

LogicSimplifier::LogicSimplifier()
{

}

QList<int> customSort(QHash<int,mergedTerms> &merged)
{
    QList<int> toReturn;

    return toReturn;
}

QString LogicSimplifier::guineMcCluskeySimplification(QList<uint> primeImplicant, QStringList inputName)
{
    /*if (varCount == -1) {
        foreach (int val, primeImplicant) {
            //TOOD
        }
    }*/
//Faire une fonction sort 

    //Step 1: Group them by the number of 1
    QHash<int, QList<int> > groups;
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
                merged[val].filter |= val ^ val2;
                merged[val].terms << val2;
            }
        }
    }

    //Step 3: Check for other passes

    //Step 4: I am not even sure about this one

}
