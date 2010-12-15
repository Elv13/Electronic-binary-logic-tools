#ifndef KARNAUGH_H
#define KARNAUGH_H

#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPalette>
#include <QBrush>
#include <QPen>
#include <QVector>

class Karnaugh : public QGraphicsItemGroup
{
public:
    explicit Karnaugh(QList<QChar> dataSet, QStringList varName, QGraphicsItem* parent = 0);

private:
    void addTable(uint variableCount, QList<QChar> dataSet, QStringList varName, uint offset=0);
    QPalette getPalette();
    QPen getTextPen();
    QBrush getRectBrush();
    QBrush getLinebrush();
    QColor getRectColor();
    QGraphicsRectItem* deepen(uint x, uint y, uint h, uint w);
    static QPalette* palette;
    static QPen* mainTextPen;
    static QBrush* mainRectBrush;
    static QBrush* lineBursh;
    static QColor* rectColor;
    QVector< QVector<QChar> > m_values;
signals:

public slots:

};

#endif // KARNAUGH_H
