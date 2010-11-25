#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    uint testTruthIn;
    uint testTruthOut;

private slots:
    void updateEquations();
    void resizeTable();

};

#endif // MAINWINDOW_H
