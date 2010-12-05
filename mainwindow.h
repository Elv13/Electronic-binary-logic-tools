#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLine>
#include <QPen>
#include "gatebase.h"
#include "circuitline.h"
#include "equationeditor.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void generateTable(uint input, uint output);
    QGraphicsItemGroup* connectGates(GateBase* gate1, GateBase* gate2, bool invert = false);
    void drawGate();
    uint testTruthIn;
    uint testTruthOut;
    QGraphicsScene* scene;
    QList<CircuitLine*> lineList;
    EquationEditor* equationEditor;
private slots:
    void updateEquations();
    void resizeTable();
    void modeTruth();
    void modeAnalyse();
    void modeCircuit();
    void modeAlgebra();
};

#endif // MAINWINDOW_H
