#include "equationeditor.h"

#include <QLabel>
#include <QLineEdit>

EquationEditor::EquationEditor(QWidget *parent) :
    QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    addLine("test","A'B'CD'E + A'BCDE' + AB'C'D'E");
    addLine("test2","A'BC'D'E + A'BC'DE' + A'BCD'E' + A'BCDE + ABCD'E' + ABCD'E");
}



void EquationEditor::addLine(QString inputName, QString equation)
{
    QLabel* outLabel =  new QLabel(inputName + " = ",this);
    QLineEdit* anEquation = new QLineEdit(this);
    anEquation->setText(equation);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(outLabel);
    layout->addWidget(anEquation);

    mainLayout->addItem(layout);

    m_equationList[inputName] = anEquation;
}

void EquationEditor::setEquation(QString inputName, QString equation)
{

}

QString EquationEditor::equation(QString inputName)
{

}

QHash<QString, QString> EquationEditor::equationList()
{
    QHash<QString, QString> toReturn;
    foreach (QLineEdit* line,m_equationList) {
        toReturn[m_equationList.key(line)] = line->text();
    }

    return toReturn;
}
