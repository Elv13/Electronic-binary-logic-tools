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
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsProxyWidget>
#include <QPainterPath>
#include "andgate.h"
#include "orgate.h"
#include "input.h"
#include "circuitline.h"
#include "logicsimplifier.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this))
{
    QPalette aPalette;

    ui->setupUi(this);
    circuit = new QGraphicsItemGroup();
    scene->addItem(circuit);
    equationEditor = new EquationEditor(ui->frmAlgebra);
    ui->frmAlgebra->layout()->addWidget(equationEditor);

    //ui->tabwMode->setVisible(false);
    ui->frmAlgebra->setVisible(false);
    ui->frmCircuit->setVisible(false);
    ui->frmAnalyse->setVisible(false);
    ui->frmVHDL->setVisible(false);
    ui->frmAdvancedCircuitSettings->setVisible(false);
    connect(ui->btnAlgebra,SIGNAL(clicked(bool)),this,SLOT(modeAlgebra()));
    connect(ui->btnCircuit,SIGNAL(clicked(bool)),this,SLOT(modeCircuit()));
    connect(ui->btnAnalyse,SIGNAL(clicked(bool)),this,SLOT(modeAnalyse()));
    connect(ui->btnVHDL,SIGNAL(clicked(bool)),this,SLOT(modeVHDL()));
    connect(ui->btnTruth,SIGNAL(clicked(bool)),this,SLOT(modeTruth()));
    //ui->verticalLayout_2->setContentsMargins(0,0,0,0);

    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    generateTable(5,2);
    //connect(ui->btnGenerate,SIGNAL(clicked()),this,SLOT(updateEquations()));
    connect(ui->spnInputNum,SIGNAL(valueChanged(int)),this,SLOT(resizeTable()));
    connect(ui->spnOutputNum,SIGNAL(valueChanged(int)),this,SLOT(resizeTable()));

    ui->graphicsView->setScene(scene);    

    QGraphicsItemGroup* grid = new QGraphicsItemGroup();
    QGraphicsLineItem* aLine;
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


    //Logic simulator code
    QGraphicsScene* analyserScene = new QGraphicsScene();
    ui->graAnalyserData->setScene(analyserScene);
    QGraphicsRectItem* sidePanel = new QGraphicsRectItem();
    sidePanel->setRect(0,0,150,400);
    QColor analiserSizeColor;
    analiserSizeColor.setNamedColor("#999999");
    sidePanel->setZValue(-100);
    sidePanel->setBrush(analiserSizeColor);
    analyserScene->addItem(sidePanel);

    QGraphicsItemGroup* grid2 = new QGraphicsItemGroup();
    grid2->setZValue(-200);
    for (int i =150;i<2900;i+=75) {
        QGraphicsLineItem* line = new QGraphicsLineItem(grid2);
        line->setLine(i,25,i,399);
        grid2->addToGroup(line);
        QGraphicsSimpleTextItem* time = new QGraphicsSimpleTextItem(grid2);
        time->setText(QString::number(i)+"ms");
        time->setPos(i,5);
        grid2->addToGroup(time);
    }
    analyserScene->addItem(grid2);

    QGraphicsItemGroup* hGrid = new QGraphicsItemGroup();
    for (int i =0;i<300;i+=30) {
        QGraphicsLineItem* line = new QGraphicsLineItem(hGrid);
        line->setLine(150,i,2000,i);
        hGrid->addToGroup(line);
        /*QGraphicsSimpleTextItem* time = new QGraphicsSimpleTextItem(grid2);
        time->setText(QString::number(i)+"ms");
        time->setPos(i,5);
        grid2->addToGroup(time);*/
    }
    analyserScene->addItem(hGrid);

    QGraphicsItemGroup* sideGroup = new QGraphicsItemGroup();
    for (int i =0;i<300;i+=30) {
        QGraphicsSimpleTextItem* time = new QGraphicsSimpleTextItem(sideGroup);
        time->setText(QString::number(i));
        time->setPos(20,i);
        sideGroup->addToGroup(time);

        QComboBox* cbbValue = new QComboBox();
        QStringList valList;
        valList << "0" << "1" << "X";
        cbbValue->addItems(valList);
        QGraphicsProxyWidget* cbbValueProxy = analyserScene->addWidget(cbbValue);
        cbbValueProxy->setPos(80,i);
        sideGroup->addToGroup(cbbValueProxy);
    }
    analyserScene->addItem(sideGroup);

    //Draw a Karnaugh table
    kmapScene = new QGraphicsScene(this);
    ui->graVHDL->setScene(kmapScene);

    QGraphicsItemGroup* grpKarnaugh = new QGraphicsItemGroup();
    int variableCount = 4;
    char *truthTable[] = {"0","1","2","3","4","5","1","1","1","1","1","1","1","1","1","1"};

    QGraphicsLineItem* aLine3 = new QGraphicsLineItem(grpKarnaugh);
    aLine3->setLine(0,0,25,25);
    grpKarnaugh->addToGroup(aLine3);

    for (int i=0;i<((variableCount/2 + variableCount%2)*2 + 1)*50;i+=50) {
        QGraphicsLineItem* aLine2 = new QGraphicsLineItem(grpKarnaugh);
        aLine2->setLine(i+25,25,i+25,(variableCount == 4)?225:125);
        grpKarnaugh->addToGroup(aLine2);
        QGraphicsSimpleTextItem* colName = new QGraphicsSimpleTextItem;
        colName->setPos(i+25,0);
        colName->setText(LogicSimplifier::dec2bin(LogicSimplifier::greyCodeGenerator(i/50),1));
        grpKarnaugh->addToGroup(colName);
    }

    for (int i=0;i<((variableCount == 4)?5:3)*50;i+=50) {
        QGraphicsLineItem* aLine2 = new QGraphicsLineItem(grpKarnaugh);
        aLine2->setLine(25,i+25,(variableCount >= 3)?225:125,i+25);
        grpKarnaugh->addToGroup(aLine2);

        QGraphicsSimpleTextItem* rowName = new QGraphicsSimpleTextItem;
        rowName->setPos(0,i+25);
        rowName->setText(LogicSimplifier::dec2bin(LogicSimplifier::greyCodeGenerator(i/50),1));
        grpKarnaugh->addToGroup(rowName);
    }

    for (int i=0;i<1<<variableCount;i++) {
        QGraphicsSimpleTextItem* value = new QGraphicsSimpleTextItem;
        value->setText(QString("t")+truthTable[LogicSimplifier::greyCodeGenerator(i)]);

        QGraphicsSimpleTextItem* rowName = new QGraphicsSimpleTextItem;
        if (i/variableCount %2) {
            rowName->setPos(i/variableCount * 50 + 25,(((variableCount == 4)?3:1)-i%variableCount) * 50 + 25);
            value->setPos(i/variableCount * 50 + 45,(((variableCount == 4)?3:1)-i%variableCount) * 50 + 45);
        }
        else {
            rowName->setPos(i/variableCount * 50 + 25,i%variableCount * 50 + 25);
            value->setPos(i/variableCount * 50 + 45,i%variableCount * 50 + 45);
        }
        rowName->setText(QString::number(LogicSimplifier::greyCodeGenerator(i)));
        grpKarnaugh->addToGroup(rowName);
        grpKarnaugh->addToGroup(value);

    }

    for (int i=0;i<16;i++) {
        qDebug() << "(" << i << ")" << LogicSimplifier::dec2bin(LogicSimplifier::greyCodeGenerator(i),3);
    }

    kmapScene->addItem(grpKarnaugh);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawGate()
{
    //Clear the old one, this apps is not resigned to edit anything, it is just to display it
    foreach( QGraphicsItem *item, scene->items( circuit->boundingRect() ) ) {
        if( item->group() == circuit ) {
            circuit->removeFromGroup(item);
            delete item;
        }
    }
    lineList.clear();

    QStringList sum;
    QString tmp;
    QString output;

    QHash<QString,Input*> inputs;

    //TODO remove this, find why it crash
    /*inputs["A"] = new Input("A");
    inputs["B"] = new Input("B");
    inputs["C"] = new Input("C");

    inputs["A"]->setPos(250,50);
    inputs["B"]->setPos(250,100);
    inputs["C"]->setPos(250,150);

    scene->addItem(inputs["A"]);
    scene->addItem(inputs["B"]);
    scene->addItem(inputs["C"]);*/



    int yInOfsset=50;
    for (int i=0;i<ui->tblTruthTest->columnCount()-1;i++) {
        qDebug() << "This is the text" << ((QLineEdit*)ui->tblTruthTest->cellWidget(0,i))->text();
        QString inputName = ((QLineEdit*)ui->tblTruthTest->cellWidget(0,i))->text();
        inputs[inputName] = new Input(inputName);
        inputs[inputName]->setPos(0,yInOfsset*(i+1));
        circuit->addToGroup(inputs[inputName]);
    }

    //QStringList equations = ui->txtAlgebra->toPlainText().replace(QChar(0x2029),QString("\n")).split("\n");
    //QStringList equations;
    //equations << "F = A'B'CD'E + A'BCDE' + AB'C'D'E" << "G = A'BC'D'E + A'BC'DE' + A'BCD'E' + A'BCDE + ABCD'E' + ABCD'E";
    QHash<QString, QString> equations = equationEditor->equationList();
    foreach (QString anEquation,equations) {
        qDebug() << "This is the equation: " << anEquation;
        for (int i=0;i<anEquation.count();i++) {
            output = equations.key(anEquation);
            /*if (anEquation[i] == '=') {
                tmp = tmp.trimmed();
                output = tmp;
                tmp.clear();
            }
            else */if (anEquation[i] == '+') {
                tmp = tmp.trimmed();
                sum << tmp;
                tmp.clear();
            }
            else {
                tmp += anEquation[i];
            }
        }

        tmp = tmp.trimmed();
        sum << tmp;
        tmp.clear();

        //Could have some recursivity here
        //auto function = [&](int x, int y) { return x + y; }
        int yOfsset = 0;
        foreach(QString aSum,sum) {
            AndGate* aGate3 = new AndGate(this,2);
            aGate3->setPos(150,yOfsset+=50);
            circuit->addToGroup(aGate3);
            for (int i=0;i<aSum.count();i++) {
                if (aSum[i] != '\'')
                    circuit->addToGroup(connectGates(inputs[ QString(aSum[i]) ],aGate3,(i < aSum.count() && aSum[i+1]!='\'')?false:true));
            }
        }
    }



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

    for (uint i=0; i < lines; i++) {
        int tmp = 16;
        for (uint j =0;j < input;j++ ) {
            QTableWidgetItem* newItem = new QTableWidgetItem(QString::number(!!(i&tmp))); //locic_not * logic_not * i binary_or tmp = 1 or 0
            newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
            newItem->setTextAlignment(Qt::AlignCenter);
            ui->tblTruthTest->setItem(i+1,j, newItem);
            tmp /= 2;
        }

        if (output > 0) {
            for (uint out=0; out < output; out++) {
                QComboBox* cbbAValue = new QComboBox();
                cbbAValue->addItems(possibilities);
                ui->tblTruthTest->setCellWidget(i+1,out+input,cbbAValue);
            }
        }
        QTableWidgetItem* header = new QTableWidgetItem(QString::number(i));
        header->setTextAlignment(Qt::AlignCenter);
        ui->tblTruthTest->setVerticalHeaderItem(i+1,header);
    }

    for (uint i =0; i< input+output;i++) {
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

    for (uint lines=1;lines<ui->tblTruthTest->rowCount();lines++) {
        for (uint out =0; out < testTruthOut;out++) {
            QString value = ((QComboBox*)ui->tblTruthTest->cellWidget(lines,out+testTruthIn))->currentText();
            if (value == "1") {
                output[out] += " + ";
                for (uint input=0;input<testTruthIn;input++) {
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
        for (uint out =0; out < testTruthOut;out++)
            outList << (((QLineEdit*)ui->tblTruthTest->cellWidget(0,testTruthIn+out))->text());
        QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("You are about to delete an output, all data from this output will be lost.\nSelect the desired output:"), outList, 0, false, &ok);

       // if (ok && !item.isEmpty())
       //     itemLabel->setText(item);
    }
    else if (ui->spnInputNum->value()<testTruthIn) {
        QStringList inList;
        bool ok;
        for (uint in =0; in < testTruthIn; in++)
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


QGraphicsItemGroup* MainWindow::connectGates(GateBase* gate1, GateBase* gate2, bool invert)
{

    QGraphicsItemGroup* aGroup = new QGraphicsItemGroup();
    QLine hLine1;
    QPoint inputPoint = gate2->addParentGate(gate1,invert);
    uint preferedPos = gate1->pos().x()+gate1->outputRelCoord().x()  +  (((gate2->pos().x()+inputPoint.x())-gate1->pos().x())/4);//(inputPoint.x()-(gate1->pos().x()));///2 + 5;
    bool ok = true;

    //TODO merge lines with the same sources when necessary
    while (true) {
        foreach (CircuitLine* aLine, lineList) {
            if (aLine->m_gate1 == gate1) {
                break;
            }
            else if ((aLine->line().x1() == preferedPos) || (aLine->line().x2() == preferedPos)) {
                preferedPos +=10;
                ok = false;
                break;
            }
        }
        if (ok)
            break;
        else
            ok = true;
    }

    QPoint point1(gate1->pos().x()+gate1->outputRelCoord().x(),gate1->pos().y()+gate1->outputRelCoord().y());
    QPoint point2(preferedPos,gate1->pos().y()+gate1->outputRelCoord().y());
    QPoint point3(preferedPos,gate2->pos().y()+inputPoint.y());
    QPoint point4(gate2->pos().x()+inputPoint.x(),gate2->pos().y()+inputPoint.y());

    QLine line1(point1,point2);
    QLine line2(point2,point3);
    QLine line3(point3,point4);



    CircuitLine* ghLine1 = new CircuitLine(line1,gate1,gate2,aGroup);
    aGroup->addToGroup(ghLine1);

    CircuitLine* gyLine = new CircuitLine(line2,gate1,gate2,aGroup);
    aGroup->addToGroup(gyLine);

    CircuitLine* ghLine2 = new CircuitLine(line3,gate1,gate2,aGroup);
    aGroup->addToGroup(ghLine2);

    lineList << ghLine1 << gyLine << ghLine2;

    /*QPoint point1 = QPoint(gate1->pos().x()+gate1->outputRelCoord().x(),gate1->pos().y()+gate1->outputRelCoord().y());
    QPoint inputPoint = gate2->addInput(invert);
    QPoint point2 = QPoint(gate2->pos().x()+inputPoint.x(),gate2->pos().y()+inputPoint.y());
    QGraphicsLineItem* aLine = new QGraphicsLineItem(point1.x(),point1.y(),point2.x(),point2.y());
    aGroup->addToGroup(aLine);*/

    return aGroup;
}


void MainWindow::modeTruth()
{
    ui->frmTruth->setVisible(true);
    ui->frmAlgebra->setVisible(false);
    ui->frmCircuit->setVisible(false);
    ui->frmAnalyse->setVisible(false);
    ui->frmVHDL->setVisible(false);

    ui->btnAlgebra->setChecked(false);
    ui->btnCircuit->setChecked(false);
    ui->btnAnalyse->setChecked(false);
    ui->btnVHDL->setChecked(false);
}

void MainWindow::modeAnalyse()
{
    ui->frmTruth->setVisible(false);
    ui->frmAlgebra->setVisible(false);
    ui->frmCircuit->setVisible(false);
    ui->frmAnalyse->setVisible(true);
    ui->frmVHDL->setVisible(false);

    ui->btnTruth->setChecked(false);
    ui->btnAlgebra->setChecked(false);
    ui->btnCircuit->setChecked(false);
    ui->btnVHDL->setChecked(false);
}

void MainWindow::modeCircuit()
{
    ui->frmTruth->setVisible(false);
    ui->frmAlgebra->setVisible(false);
    ui->frmCircuit->setVisible(true);
    ui->frmAnalyse->setVisible(false);
    ui->frmVHDL->setVisible(false);

    ui->btnTruth->setChecked(false);
    ui->btnAlgebra->setChecked(false);
    ui->btnVHDL->setChecked(false);
    ui->btnAnalyse->setChecked(false);
    updateEquations();

}

void MainWindow::modeVHDL()
{
    ui->frmTruth->setVisible(false);
    ui->frmAlgebra->setVisible(false);
    ui->frmCircuit->setVisible(false);
    ui->frmAnalyse->setVisible(false);
    ui->frmVHDL->setVisible(true);

    ui->btnTruth->setChecked(false);
    ui->btnAlgebra->setChecked(false);
    ui->btnAnalyse->setChecked(false);
    ui->btnVHDL->setChecked(false);
    updateEquations();

}

void MainWindow::modeAlgebra()
{
    ui->frmTruth->setVisible(false);
    ui->frmAlgebra->setVisible(true);
    ui->frmCircuit->setVisible(false);
    ui->frmAnalyse->setVisible(false);

    ui->btnTruth->setChecked(false);
    ui->btnCircuit->setChecked(false);
    ui->btnAnalyse->setChecked(false);
    ui->btnVHDL->setChecked(true);
    updateEquations();
    drawGate();
}
