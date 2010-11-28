#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QHash>
#include <QDebug>
#include <QChar>
#include <QHeaderView>
#include <QLineEdit>
#include <QPalette>
#include <QBrush>
#include <QInputDialog>
#include <QGraphicsItemGroup>
#include <QPainterPath>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPen>
#include <QColor>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include "andgate.h"
#include "orgate.h"
#include "input.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    generateTable(5,2);
    connect(ui->btnGenerate,SIGNAL(clicked()),this,SLOT(updateEquations()));
    connect(ui->spnInputNum,SIGNAL(valueChanged(int)),this,SLOT(resizeTable()));
    connect(ui->spnOutputNum,SIGNAL(valueChanged(int)),this,SLOT(resizeTable()));

    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    Input* testIn = new Input("test");

    OrGate* aGate1 = new OrGate(this,2);
    OrGate* aGate2 = new OrGate(this,2);

    AndGate* aGate3 = new AndGate(this,2);
    AndGate* aGate4 = new AndGate(this,2);

    aGate1->setPos(150,50);
    aGate2->setPos(200,50);
    aGate3->setPos(150,100);
    aGate4->setPos(200,100);

    scene->addItem(aGate1);
    scene->addItem(aGate2);
    scene->addItem(aGate3);
    scene->addItem(aGate4);
    scene->addItem(testIn);

    scene->addItem(connectGates(testIn,aGate1,false));
    scene->addItem(connectGates(testIn,aGate1,true));

    scene->addItem(connectGates(testIn,aGate3,false));
    scene->addItem(connectGates(testIn,aGate3,true));

    QGraphicsItemGroup* grid = new QGraphicsItemGroup();
    QGraphicsLineItem* aLine;
    QPalette aPalette;
    QPen majorPen;
    QColor majorColor(aPalette.background().color());
    int darkOrBright = (aPalette.background().color().blue()-40 >0)?1:-1;
    majorColor.setBlue(majorColor.blue()-(40*darkOrBright));
    majorColor.setRed(majorColor.red()-(40*darkOrBright));
    majorColor.setGreen(majorColor.green()-(40*darkOrBright));
    majorPen.setColor(majorColor);

    QPen minorPen;
    QColor minorColor(aPalette.background().color());
    minorColor.setBlue(minorColor.blue()-(10*darkOrBright));
    minorColor.setRed(minorColor.red()-(10*darkOrBright));
    minorColor.setGreen(minorColor.green()-(10*darkOrBright));
    minorPen.setColor(minorColor);

    for (int i=0; i<=1000;i+=10) {
        if ((i%50)) {
            aLine = new QGraphicsLineItem();
            aLine->setLine(i,0,i,1000);
            aLine->setPen(minorPen);
            grid->addToGroup(aLine);
        }
    }
    for (int i=0; i<=1000;i+=10) {
        if ((i%50)) {
            aLine = new QGraphicsLineItem();
            aLine->setLine(0,i,1000,i);
            aLine->setPen(minorPen);
            grid->addToGroup(aLine);
        }
    }

    for (int i=0; i<=1000;i+=50) {
        aLine = new QGraphicsLineItem();
        aLine->setLine(i,0,i,1000);
        aLine->setPen(majorPen);
        grid->addToGroup(aLine);
    }
    for (int i=0; i<=1000;i+=50) {
        aLine = new QGraphicsLineItem();
        aLine->setLine(0,i,1000,i);
        aLine->setPen(majorPen);
        grid->addToGroup(aLine);
    }
    scene->addItem(grid);
    grid->setZValue(-1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateTable(uint input, uint output)
{
    QPalette* aPalette = new QPalette();

    testTruthIn = input;
    testTruthOut = output;

    int lines =1;
    lines <<= input; //2^input
    QStringList possibilities;
    possibilities << "X" << "O" << "1";

    ui->tblTruthTest->setColumnCount(input+output);
    ui->tblTruthTest->setRowCount(lines+1);
    ui->tblTruthTest->horizontalHeader()->hide();
    ui->tblTruthTest->setVerticalHeaderItem(0, new QTableWidgetItem(""));

    for (int i=0; i < lines; i++) {
        int tmp = 16;
        for (int j =0;j < input;j++ ) {
            QTableWidgetItem* newItem = new QTableWidgetItem(QString::number(!!(i&tmp))); //locic_not * logic_not * i binary_or tmp = 1 or 0
            newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
            newItem->setTextAlignment(Qt::AlignCenter);
            ui->tblTruthTest->setItem(i+1,j, newItem);
            tmp /= 2;
        }

        if (output > 0) {
            for (int out=0; out < output; out++) {
                QComboBox* cbbAValue = new QComboBox();
                cbbAValue->addItems(possibilities);
                ui->tblTruthTest->setCellWidget(i+1,out+input,cbbAValue);
            }
        }
        QTableWidgetItem* header = new QTableWidgetItem(QString::number(i));
        header->setTextAlignment(Qt::AlignCenter);
        ui->tblTruthTest->setVerticalHeaderItem(i+1,header);
    }

    for (int i =0; i< input+output;i++) {
        ui->tblTruthTest->setColumnWidth(i,40);
        QLineEdit* aLineEdit = new QLineEdit(this);
        aLineEdit->setText({((char)i)+0x41}); //Little trick to make an alphebetical counter
        aLineEdit->setStyleSheet("background-color:"+aPalette->button().color().name()+";margin:0px;spacing:0px;text-align:center;");
        ui->tblTruthTest->setCellWidget(0,i,aLineEdit);
    }

}

void MainWindow::updateEquations()
{
    ui->txtOutTest->clear();
    QHash<int,QString> output;

    for (int lines=1;lines<ui->tblTruthTest->rowCount();lines++) {
        for (int out =0; out < testTruthOut;out++) {
            QString value = ((QComboBox*)ui->tblTruthTest->cellWidget(lines,out+testTruthIn))->currentText();
            if (value == "1") {
                output[out] += " + ";
                for (int input=0;input<testTruthIn;input++) {
                    output[out] += ((QLineEdit*)ui->tblTruthTest->cellWidget(0,input))->text()+ QString((ui->tblTruthTest->item(lines,input)->text().toInt())?"":"'");
                }
            }
        }
    }
    for (int out =0; out < testTruthOut;out++) {
        ui->txtOutTest->setPlainText(ui->txtOutTest->toPlainText()+((QLineEdit*)ui->tblTruthTest->cellWidget(0,testTruthIn+out))->text()+" ="+output[out]+"\n");
    }

}

void MainWindow::resizeTable()
{

    if (ui->spnOutputNum->value()<testTruthOut) {
        QStringList outList;
        bool ok;
        for (int out =0; out < testTruthOut;out++)
            outList << (((QLineEdit*)ui->tblTruthTest->cellWidget(0,testTruthIn+out))->text());
        QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("You are about to delete an output, all data from this output will be lost.\nSelect the desired output:"), outList, 0, false, &ok);

       // if (ok && !item.isEmpty())
       //     itemLabel->setText(item);
    }
    else if (ui->spnInputNum->value()<testTruthIn) {
        QStringList inList;
        bool ok;
        for (int in =0; in < testTruthIn;in++)
            inList << (((QLineEdit*)ui->tblTruthTest->cellWidget(0,in))->text());
        QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("You are about to delete an input, all data from this input will be lost.\nSelect the desired input:"), inList, 0, false, &ok);

    }


    ui->tblTruthTest->setColumnCount(ui->spnOutputNum->value()+ui->spnInputNum->value());

    int lines =1;
    lines <<= ui->spnInputNum->value(); //2^input
    ui->tblTruthTest->setRowCount(lines+1);



    testTruthIn = ui->spnInputNum->value();
    testTruthOut = ui->spnOutputNum->value();
}


QGraphicsLineItem* MainWindow::connectGates(GateBase* gate1, GateBase* gate2, bool invert)
{

    QPoint point1 = QPoint(gate1->pos().x()+gate1->outputRelCoord().x(),gate1->pos().y()+gate1->outputRelCoord().y());
    QPoint inputPoint = gate2->addInput(invert);
    QPoint point2 = QPoint(gate2->pos().x()+inputPoint.x(),gate2->pos().y()+inputPoint.y());
    QGraphicsLineItem* aLine = new QGraphicsLineItem(point1.x(),point1.y(),point2.x(),point2.y());
    return aLine;
}
