#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "desenharcampo.h"
#include "customscene.h"
#include "robo1.h"

#include "math.h"
#include <QtMath>

#include <QClipboard>
#include <QHostAddress>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QGraphicsLineItem>

QUdpSocket *udpSocketOut;
QUdpSocket *udpSocketIn;

QString MyAddress = "192.168.1.115";
QString DestineAddress = "192.168.1.139";

int MyPort = 1234;
int DestinePort = 1235;

int RenderWidth;
int RenderHeigth;

Robo1 *robo1;
QGraphicsLineItem *line;
QGraphicsRectItem *square;

int squareMesures = 20;

int iniX = 0, iniY = 0;
float iniAngle = 0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    RenderWidth = 482;
    RenderHeigth = 670;
    OnMove = false;

    ui->setupUi(this);

    scene = new CustomScene(this);
    QGraphicsView *view = ui->graphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(RenderWidth,RenderHeigth);

    scene->setSceneRect(-RenderWidth/2,-RenderHeigth/2,RenderWidth,RenderHeigth);

    float ComprimentoCampo = 500,LarguraCampo = 367,espessuraLinhas = 5, RaioCentro = 63.5;
    float LarguraPequenaArea = 25,ComprimentoPequenaArea = 150, LarguraGrandeArea = 67.5, ComprimentoGrandeArea = 211;
    float CantoRaio = 19.5,bolaCentralRaio = 5.875,bolaPenaltiRaio = 3.25,distanciaPenalti = 85;
    float margemEsq = 12;

    DesenharCampo *campo = new DesenharCampo();
    campo->desenharLinhas(scene,ComprimentoCampo*factor,LarguraCampo*factor,espessuraLinhas*factor,RaioCentro*factor,LarguraPequenaArea*factor,ComprimentoPequenaArea*factor,LarguraGrandeArea*factor,ComprimentoGrandeArea*factor,CantoRaio*factor,bolaCentralRaio*factor,bolaPenaltiRaio*factor,distanciaPenalti*factor,RenderWidth,margemEsq*factor);

    robo1 = new Robo1(this);
    robo1->setNumber(QString::number(1));
    robo1->setPos(-robo1->width/2,-robo1->height/2);
    scene->addItem(robo1);

    view->setScene(scene);

    initSocket();

    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             qDebug() << address.toString();
    }

    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(255,0,0));
    line = new QGraphicsLineItem();
    line->setPen(pen);

    square = new QGraphicsRectItem();

    square->setRect(-squareMesures/2,-squareMesures/2,squareMesures,squareMesures);
    square->setPen(pen);
    square->setPos(5000,5000);

    timerNewPos = new QTimer(this);
    connect(timerNewPos, SIGNAL(timeout()), this, SLOT(updatePos()));
}

void MainWindow::drawLine(int x1, int y1, int x2, int y2)
{
    scene->removeItem(line);
    line->setLine(x1,y1,x2,y2);
    scene->addItem(line);
    //scene->addLine(x1,y1,x2,y2);

    scene->removeItem(square);
    square->setPos(x2,y2);
    scene->addItem(square);

    robo1->setPos(x1-robo1->width/2,y1-robo1->height/2);
    iniX = x1-robo1->width/2;
    iniY = y1-robo1->height/2;

    float Npixeis = sqrt(pow((abs(x1-x2)),2)+pow((abs(y1-y2)),2));
    float angulo = atan2((abs(y1-y2)),(abs(x1-x2)));
    angulo = angulo*(180/M_PI);

    if(y1>y2 && x1>x2)
    {
        angulo = ((angulo-90)*-1)+90;
        //Quadrante 2
    }
    else if(y1<y2 && x1>x2)
    {
        angulo = angulo+180;
        //Quadrante 3
    }
    else if(y1<y2 && x1<x2)
    {
        angulo = ((angulo-90)*-1)+270;
        //Quadrante 4
    }

    float metros = (Npixeis*10/8)/100;
    ui->plainTextEdit->appendPlainText("Percorreu: "+QString::number(metros)+" metros");
    ui->plainTextEdit->appendPlainText("Angulo: "+QString::number(angulo));

    iniAngle = 360 - angulo;
    //timerNewPos->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSocket()
{
    udpSocketOut = new QUdpSocket(this);
    udpSocketOut->bind(QHostAddress(DestineAddress), DestinePort);

    udpSocketIn = new QUdpSocket(this);
    udpSocketIn->bind(QHostAddress(MyAddress), MyPort);
    connect(udpSocketIn, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));
}
bool encontrado = false;
void MainWindow::readPendingDatagrams()
{
    while (udpSocketIn->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketIn->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocketIn->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        QString aux = datagram;
        if(!OnMove && !encontrado)
        {
            QStringList recebido = aux.split(",");

            int xPos = recebido.at(0).toInt();
            int yPos = recebido.at(1).toInt();
            anguloRobo = (int)recebido.at(2).toFloat();
            anguloRobo+=90;
            anguloRobo = 360 - anguloRobo;

            int xReal = -(RenderWidth/2)+xPos;
            int yReal = -(RenderHeigth/2)+yPos;
            yReal = yReal*-1;
            //qDebug() <<"X: "<< xReal << " Y: " << yReal;
            //ui->plainTextEdit->appendPlainText("XREal: "+ QString::number(xReal) + " YReal: " + QString::number(yReal)+ " angulo: " + recebido[2]);
            //ui->plainTextEdit->appendPlainText(" Angulo: "+QString::number(anguloRobo));
            robo1->setPos(xReal-(robo1->width/2),yReal-(robo1->height/2));
            robo1->setAngle(anguloRobo);


            if(square->collidesWithItem(robo1))
            {
                ui->plainTextEdit->appendPlainText("Dentro!");
                //ui->plainTextEdit->appendPlainText("graus:"+QString::number(iniAngle)+"Rad:"+QString::number(qDegreesToRadians(iniAngle)));
                encontrado = true;
            }
            else if(xReal-(robo1->width/2)>RenderWidth/2 || yReal-(robo1->height/2)>RenderHeigth/2)
            {
                ui->plainTextEdit->appendPlainText("graus:"+QString::number(iniAngle)+"Rad:"+QString::number(qDegreesToRadians(iniAngle)));
                ui->plainTextEdit->appendPlainText("FIM PLANO!");
                timerNewPos->stop();
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch ( event->key())
    {
        case Qt::Key_Shift:
        OnMove = true;
        break;
        case Qt::Key_Control:
        OnMove = true;
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch ( event->key())
    {
        case Qt::Key_Shift:
        OnMove = false;
        encontrado = false;
        break;
        case Qt::Key_Control:
        OnMove = false;
        encontrado = false;
        break;
    }
}

void MainWindow::updatePos()
{
    int pixeisAdvance = 5;

    float newX = iniX + pixeisAdvance * cos(qDegreesToRadians(iniAngle));
    float newY = iniY + pixeisAdvance * sin(qDegreesToRadians(iniAngle));


    if(iniY>newY && iniX>newX)
    {
        robo1->setPos(newX,newY);
        scene->addLine(iniX,iniY,newX,newY);
        //Quadrante 2
    }
    else if(iniY<newY && iniX>newX)
    {
        robo1->setPos(newX,newY);
        scene->addLine(iniX+robo1->width/2,iniY+robo1->height/2,newX+robo1->width/2,newY+robo1->height/2);
        //Quadrante 3
    }
    else if(iniY<newY && iniX<newX)
    {
        robo1->setPos(newX,newY);
        scene->addLine(iniX,iniY,newX,newY);
        //Quadrante 4
    }
    else
    {
        robo1->setPos(newX,newY);
        scene->addLine(iniX+robo1->width/2,iniY+robo1->height/2,newX+robo1->width/2,newY+robo1->height/2);
        //Quadrante 1
    }
    //ui->plainTextEdit->appendPlainText("X:"+QString::number(newX)+" Y:"+QString::number(newY)+" Rad:"+QString::number(qDegreesToRadians(iniAngle)));


    iniX = newX;
    iniY = newY;


    if(square->collidesWithItem(robo1))
    {
        //ui->plainTextEdit->appendPlainText("Dentro!");
        ui->plainTextEdit->appendPlainText("graus:"+QString::number(iniAngle)+"Rad:"+QString::number(qDegreesToRadians(iniAngle)));
        timerNewPos->stop();
    }
    else if(newX>RenderWidth/2 || newY>RenderHeigth/2)
    {
        ui->plainTextEdit->appendPlainText("graus:"+QString::number(iniAngle)+"Rad:"+QString::number(qDegreesToRadians(iniAngle)));
        ui->plainTextEdit->appendPlainText("FIM PLANO!");
        timerNewPos->stop();
    }
}

void MainWindow::on_bt_osbt_clicked()
{
    timerNewPos->stop();
}

void MainWindow::on_btClear_2_clicked()
{
    OnMove = false;
    encontrado = false;

    scene->clear();
    float ComprimentoCampo = 500,LarguraCampo = 367,espessuraLinhas = 5, RaioCentro = 63.5;
    float LarguraPequenaArea = 25,ComprimentoPequenaArea = 150, LarguraGrandeArea = 67.5, ComprimentoGrandeArea = 211;
    float CantoRaio = 19.5,bolaCentralRaio = 5.875,bolaPenaltiRaio = 3.25,distanciaPenalti = 85;
    float margemEsq = 12;

    DesenharCampo *campo = new DesenharCampo();
    campo->desenharLinhas(scene,ComprimentoCampo*factor,LarguraCampo*factor,espessuraLinhas*factor,RaioCentro*factor,LarguraPequenaArea*factor,ComprimentoPequenaArea*factor,LarguraGrandeArea*factor,ComprimentoGrandeArea*factor,CantoRaio*factor,bolaCentralRaio*factor,bolaPenaltiRaio*factor,distanciaPenalti*factor,RenderWidth,margemEsq*factor);

    robo1 = new Robo1(this);
    robo1->setNumber(QString::number(1));
    robo1->setPos(-robo1->width/2,-robo1->height/2);
    scene->addItem(robo1);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(255,0,0));
    line = new QGraphicsLineItem();
    line->setPen(pen);

    square = new QGraphicsRectItem();

    square->setRect(-squareMesures/2,-squareMesures/2,squareMesures,squareMesures);
    square->setPen(pen);
    square->setPos(5000,5000);
}
