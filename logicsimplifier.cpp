#include "logicsimplifier.h"

#include <QHash>

LogicSimplifier::LogicSimplifier()
{

}

QString LogicSimplifier::guineMcCluskeySimplification(QList<uint> primeImplicant, QStringList inputName)
{
    /*if (varCount == -1) {
        foreach (int val, primeImplicant) {
            //TOOD
        }
    }*/

    //Step 1: Group them by the number of 1
    QHash<int, QList<int> > groups;
    foreach (int val,primeImplicant) {
        int numOfOne = 0;
        for (int i=1;i<=(1<<inputName.count());i<<1) {
            numOfOne += val&i;
        }
        groups[numOfOne] << val;
    }

    //Step 2: Compare with (number of 1) + 1, output pairs
    //with a for with (>>1)&(int)0x01
    QList< QList< QList<char> > > level2Out;
    int currentIndex =0;
    for (int i=1;i<inputName.count()-1;i++) {
        foreach (int val, groups[i]) {
            QList<char> tmpItem;
            for (int j=1;j<=(1<<inputName.count());j<<1) { //BUG compare it with itself
                if ((val&(1<<j)) != (val|(1<<j)))
                    tmpItem << '-';
                else
                    tmpItem << !!(val&(1<<j));
            }
            if (tmpItem.indexOf('-') != -1)
                level2Out[i] << tmpItem;
        }
    }

    //Step 3: Check for other passes

    //Step 4: I am not even sure about this one

}
