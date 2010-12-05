#ifndef EQUATIONEDITOR_H
#define EQUATIONEDITOR_H

#include <QWidget>
#include <QHash>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>

class EquationEditor : public QWidget
{
    Q_OBJECT
public:
    explicit EquationEditor(QWidget *parent = 0);
    void addLine(QString inputName, QString equation);
    void setEquation(QString inputName, QString equation);
    QString equation(QString inputName);
    QHash<QString, QString> equationList();
private:
    QVBoxLayout* mainLayout;
    QHash<QString, QLineEdit*> m_equationList;
signals:

public slots:

};

#endif // EQUATIONEDITOR_H
