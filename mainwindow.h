#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "gatebase.h"

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
    QGraphicsLineItem* connectGates(GateBase* gate1, GateBase* gate2, bool invert = false);
    void drawGate();
    uint testTruthIn;
    uint testTruthOut;
    QGraphicsScene* scene;
private slots:
    void updateEquations();
    void resizeTable();

};

#endif // MAINWINDOW_H
