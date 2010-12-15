#include "karnaugh.h"
#include "logicsimplifier.h"
#include <QDebug>

QPalette* Karnaugh::palette = 0;
QPen* Karnaugh::mainTextPen = 0;
QBrush* Karnaugh::lineBursh = 0;
QBrush* Karnaugh::mainRectBrush = 0;
QColor* Karnaugh::rectColor = 0;

Karnaugh::Karnaugh(QList<QChar> dataSet, QStringList varName, QGraphicsItem* parent) :
    QGraphicsItemGroup()
{
    addTable(varName.size(),dataSet,varName);
}

void Karnaugh::addTable(uint variableCount,QList<QChar> dataSet, QStringList varName,uint offset)
{

    //Draw the table

    QGraphicsLineItem* aLine3 = new QGraphicsLineItem(this);
    aLine3->setLine(0,0,25,25);
    aLine3->setPen(getTextPen());
    this->addToGroup(aLine3);

    uint rowCount = (1<<variableCount) / variableCount;
    uint colCount = (1<<variableCount) / rowCount;
    m_values.resize(rowCount);

    for (int i=0;i<=colCount*50;i+=50) {
        QGraphicsLineItem* aLine2 = new QGraphicsLineItem(this);
        aLine2->setLine(i+25,25,i+25,rowCount*50+25);
        aLine2->setPen(getTextPen());
        this->addToGroup(aLine2);
        if (i != colCount*50) {
            QGraphicsSimpleTextItem* colName = new QGraphicsSimpleTextItem;
            colName->setPos(i+25,0);
            colName->setText(LogicSimplifier::dec2bin(LogicSimplifier::greyCodeGenerator(i/50),colCount/2));
            colName->setPen(getTextPen());
            this->addToGroup(colName);
        }
    }

    for (int i=0;i<=rowCount*50;i+=50) {
        QGraphicsLineItem* aLine2 = new QGraphicsLineItem(this);
        aLine2->setLine(25,i+25,colCount*50+25,i+25);
        aLine2->setPen(getTextPen());
        this->addToGroup(aLine2);

        if (i != rowCount*50) {
            m_values[i/50].resize(colCount);
            QGraphicsSimpleTextItem* rowName = new QGraphicsSimpleTextItem;
            rowName->setPos(0,i+25);
            rowName->setText(LogicSimplifier::dec2bin(LogicSimplifier::greyCodeGenerator(i/50),rowCount/2));
            rowName->setPen(getTextPen());
            this->addToGroup(rowName);
        }
    }

    for (int i=0;i<1<<variableCount;i++) {
        QGraphicsSimpleTextItem* value = new QGraphicsSimpleTextItem;
        value->setText(dataSet[i]);
        QGraphicsSimpleTextItem* rowName = new QGraphicsSimpleTextItem;
        rowName->setPos((i/rowCount * 50) + 25,(i%rowCount) * 50 + 25);
        m_values[i%rowCount][i/rowCount] = dataSet[i];
        value->setPos(LogicSimplifier::greyCodeGenerator(i/rowCount) *50 + 45,LogicSimplifier::greyCodeGenerator(i%rowCount) * 50 + 45);
        rowName->setText(QString::number((LogicSimplifier::greyCodeGenerator(i/rowCount)<<(rowCount/2))|LogicSimplifier::greyCodeGenerator(i%rowCount)));
        value->setPen(getTextPen());
        rowName->setPen(getTextPen());
        this->addToGroup(rowName);
        this->addToGroup(value);
    }

    //Start optimisation
    qDebug() << m_values;
    for (int i=0;i<rowCount;i++) {
        for (int j=0;j<colCount;j++) {
            if (m_values[i][j] == '1')
                deepen(j,i,1,1);
        }
    }
}

QGraphicsRectItem* Karnaugh::deepen(uint x, uint y, uint h, uint w)
{
    qDebug() << x <<y <<w <<h;
    bool stillTrue(true),stillTrueH(true);
    //the width can only double
    if (w < m_values[0].size()) {
        for (int i=1;i<=w;i++) {
            uint tmpValW = (x+i>m_values.size()-1)?0:x+i;
            for (int j=1;j<=h;j++) {
                uint tmpValH = (y+i>m_values[0].size()-1)?0:y+i;
                QChar val = m_values[tmpValH][tmpValW];
                if (!((val == '1') || (val == 'X'))) {
                    stillTrue = false;
                    break;
                }
            }
            if (!stillTrue)
                break;
        }
    }
    else
        stillTrue = false;
    if (stillTrue)
        w *=2;

    if (h < m_values.size()) {
        for (int i=1;i<=h;i++) {
            uint tmpValH = (y+i>m_values[0].size()-1)?0:y+i;
            for (int j=1;j<=w;j++) {
                uint tmpValW = (x+i>m_values[0].size()-1)?0:x+i;
                QChar val = m_values[tmpValH][tmpValW];
                if (!((val == '1') || (val == 'X'))) {
                    stillTrueH = false;
                    break;
                }
            }
            if (!stillTrueH)
                break;
        }
    }
    else
        stillTrueH = false;

    if (stillTrueH)
        h *=2;

    if (stillTrue | stillTrueH) {
        deepen(x,y,h,w);
    }
    else {
        qDebug() << "end " << w <<h;
        QGraphicsRectItem* aRect = new QGraphicsRectItem(this);
        aRect->setRect(x*50+25,y*50+25,w*50,h*50);
        //TODO
        /*foreach square, check if it is needed to have this group or it is part of 1+ bigger ones*/
        aRect->setBrush(getRectColor());
        this->addToGroup(aRect);
    }

}

QPalette Karnaugh::getPalette()
{
    if (!palette) {
        palette = new QPalette();
    }
    return *palette;
}


QPen Karnaugh::getTextPen()
{
    if (!mainTextPen) {
        mainTextPen = new QPen();
        mainTextPen->setBrush(getPalette().text());
    }
    return *mainTextPen;
}


QBrush Karnaugh::getLinebrush()
{
    if (!lineBursh) {
        lineBursh = new QBrush();
    }
   return *lineBursh;
}

QBrush Karnaugh::getRectBrush()
{
    if (!mainRectBrush) {

        mainRectBrush = new QBrush();
    }
    return *mainRectBrush;
}

QColor Karnaugh::getRectColor()
{
    if (!mainRectBrush) {
        rectColor = new QColor();
        rectColor->setNamedColor("#7799FF");
        rectColor->setAlpha(155);
    }
    return *rectColor;
}
