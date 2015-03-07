#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "desenharcampo.h"
#include "customscene.h"
#include "robo1.h"
#include "ball.h"
#include "obstaculo.h"


#include <QTime>
#include <QPoint>
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <qmath.h>
#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QIODevice>
#include <QDataStream>
#include <QDir>
#include <QGraphicsLineItem>
#include "math.h"

#include <QClipboard>
#include "QHostAddress"
#include <QUdpSocket>

QUdpSocket *udpSocketOut;
QUdpSocket *udpSocketIn;

QString MyAddress = "193.136.12.69";
QString DestineAddress = "193.136.12.120";

int MyPort = 1234;
int DestinePort = 1235;

Robo1 *robo1 = new Robo1();
Ball *ball1 = new Ball();
Obstaculo *obs = new Obstaculo();

Obstaculo *obstaculos[36];

QStringList myList;

int RenderWidth;
int RenderHeigth;

float values[5500][72];
int lines = 0;

int anguloInicial = 0;
int anguloFinal = 72;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    RenderWidth = 482;
    RenderHeigth = 670;

    ui->setupUi(this);

    this->installEventFilter(this);

    for(int u=0;u<36;u++)
    {
        obstaculos[u] = new Obstaculo();
    }

    scene = new CustomScene(this);
    QGraphicsView *view = ui->graphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(RenderWidth,RenderHeigth);

    scene->setSceneRect(-RenderWidth/2,-RenderHeigth/2,RenderWidth,RenderHeigth);

    QBrush brush(QColor(0,255,0));
    QPen pen(QColor (255,255,255));
    pen.setWidth(1);
    scene->addRect(-RenderWidth/2,-RenderHeigth/2,RenderWidth,RenderHeigth,pen,brush);

    view->setScene(scene);

    float ComprimentoCampo = 500,LarguraCampo = 367,espessuraLinhas = 5, RaioCentro = 63.5;
    float LarguraPequenaArea = 25,ComprimentoPequenaArea = 150, LarguraGrandeArea = 67.5, ComprimentoGrandeArea = 211;
    float CantoRaio = 19.5,bolaCentralRaio = 5.875,bolaPenaltiRaio = 3.25,distanciaPenalti = 85;
    float margemEsq = 12;

    DesenharCampo *campo = new DesenharCampo();
    campo->desenharLinhas(scene,ComprimentoCampo*factor,LarguraCampo*factor,espessuraLinhas*factor,RaioCentro*factor,LarguraPequenaArea*factor,ComprimentoPequenaArea*factor,LarguraGrandeArea*factor,ComprimentoGrandeArea*factor,CantoRaio*factor,bolaCentralRaio*factor,bolaPenaltiRaio*factor,distanciaPenalti*factor,RenderWidth,margemEsq*factor);

    robo1->setNumber(QString::number(1));
    robo1->setPos(-robo1->width/2,-robo1->height/2);
    scene->addItem(robo1);

    ball1->setNumber(QString::number(1));
    ball1->setPos(-ball1->width/2,-ball1->height/2);
    scene->addItem(ball1);

    obs->setPos(2000,2000);
    scene->addItem(obs);

    if(!readFile("Metros.txt"))
    {
        QMessageBox::information(0, "Error: ","Enable to read file");
    }

    qDebug() <<"Lines: "<< lines;

    splitValues();

    initSocket();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btPosition_clicked()
{
    QTime t;
    t.start();
    int posNow = getPosition(ui->tbFile->text());
    //qDebug() << "Time: " << t.elapsed() <<" ms";
    int xPos = (int)(posNow/84)*8;
    int yPos = (int)(posNow%84)*8;
    ui->plainTextEdit->appendPlainText("X: "+ QString::number(xPos) + " Y: " + QString::number(yPos) + " Line" + QString::number(posNow+1));
    //qDebug() <<"X: "<< xPos << " Y: " << yPos << " Line" << posNow+1;
    //ui->plainTextEdit->appendPlainText("X: "+ QString::number(xPos) + " Y: " + QString::number(yPos) + " Line" + QString::number(posNow+1));
    int xReal = -(RenderWidth/2)+xPos;
    int yReal = -(RenderHeigth/2)+yPos;
    yReal = yReal*-1;
    //qDebug() <<"X: "<< xReal << " Y: " << yReal << " Line" << posNow+1;
    ui->plainTextEdit->appendPlainText("XREal: "+ QString::number(xReal) + " YReal: " + QString::number(yReal) + " Line" + QString::number(posNow+1));
    robo1->setPos(xReal-(robo1->width/2),yReal-(robo1->height/2));
}

bool MainWindow::readFile(QString FileName)
{
    QFile file(FileName);

    if(!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QTextStream in(&file);

    QTime t;
    t.start();
    while(!in.atEnd()) {
        myList.append(in.readLine());
        lines++;
    }
    qDebug() << t.elapsed();
    file.close();

    return true;
}

void MainWindow::splitValues()
{
    for(int k=0;k<lines-1;k++)
    {
            QStringList vector;
            vector = myList.at(k).split(",");
            for(int a = 0;a<vector.length();a++)
            {
                values[k][a] = vector.at(a).toFloat();
            }
    }
}

int MainWindow::getPosition(QString distances)
{
    QFile file;
    file.setFileName("errors.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
            QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream out(&file);



    QStringList vector = distances.split(",");
    float vars[80],error = 0,minError = 50000;
    int posNow = 0;
    int vectorRead[72];
    for(int q=0;q<vector.length();q++)
    {
        if(vector.at(q)!="x")
        {
           vars[q] = vector.at(q).toFloat();
           vectorRead[q] = 1;
           //qDebug() << 1;
        }
        else
        {
            vectorRead[q] = 0;
            //qDebug() << 0;
        }

    }

    for(int k=0;k<lines-1;k++)
    {
        for(int a = anguloInicial;a<anguloFinal;a++)
        {
            if(vectorRead[a]!=0)
            {
                error += fabs(vars[a] - values[k][a]);
            }
        }
        out << error << "\n";
        if(error<minError)
        {
            minError = error;
            posNow = k;
        }
        error = 0;
    }

    file.close();

    return posNow;
}

bool MainWindow::eventFilter(QObject *ob, QEvent *ev)
{
    if(ev->type()== QEvent::MouseButtonDblClick)
    {
        QPoint p = ui->graphicsView->mapFromGlobal(QCursor::pos());

        int xPointCenter = p.x()- RenderWidth/2;
        int yPointCenter = p.y()- RenderHeigth/2;
        ui->plainTextEdit->appendPlainText("X: "+QString::number(xPointCenter)+"Y: " + QString::number(yPointCenter));
        /*qDebug() << "X: " << xPointCenter;
        qDebug() << "Y: " <<yPointCenter;*/
    }
    else if(ev->type()== QEvent::MouseButtonPress)
    {
        /*if(Qt::RightButton)
        {
            qDebug() << "Right";
            QClipboard *cb = QApplication::clipboard();
            cb->setText(ClipBoardAdd);
        }*/
    }

    return false;
}

void MainWindow::on_dial_sliderMoved(int position)
{
    robo1->setAngle(position);
    anguloRobo = position;
}

void MainWindow::initSocket()
{
    udpSocketOut = new QUdpSocket(this);
    udpSocketOut->bind(QHostAddress(DestineAddress), DestinePort);

    udpSocketIn = new QUdpSocket(this);
    udpSocketIn->bind(QHostAddress(MyAddress), MyPort);
    connect(udpSocketIn, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));
}

void MainWindow::readPendingDatagrams()
{
    while (udpSocketIn->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketIn->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocketIn->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);


        //ui->plainTextEdit->appendPlainText(datagram);

        /*int posNow = getPosition(datagram);
        int xPos = (int)(posNow/84)*8;
        int yPos = (int)(posNow%84)*8;
        ui->plainTextEdit->appendPlainText("X: "+ QString::number(xPos) + " Y: " + QString::number(yPos) + " Line" + QString::number(posNow+1));
        qDebug() <<"X: "<< xPos << " Y: " << yPos << " Line" << posNow+1;*/
        QString aux = datagram;
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
        ui->plainTextEdit->appendPlainText(" Angulo: "+QString::number(anguloRobo));
        robo1->setPos(xReal-(robo1->width/2),yReal-(robo1->height/2));
        robo1->setAngle(anguloRobo);


        float distanciaBola = recebido.at(3).toFloat()*100;
        float anguloBola = recebido.at(4).toFloat();

        float pixeis = distanciaBola*8/10;
        pixeis += 9;



        float y = sin((360-anguloRobo+anguloBola)*(1/57.3))*pixeis;
        float x = cos((360-anguloRobo+anguloBola)*(1/57.3))*pixeis;

        qDebug() <<"Pixeis : "<< pixeis << "anguloBola: " <<anguloBola;

        if(anguloBola ==0 && pixeis == 9)
        {
            ball1->setPos(2000,2000);
            //qDebug() << "Not seen";
        }
        else
        {
            //qDebug() << "X: " << x << " Y:" << y;
            ball1->setPos((robo1->pos().x()+robo1->width/2)+x,(robo1->pos().y()+robo1->height/2)+y);
        }
        //qDebug() << "anguloBola: " << anguloBola << " pixeis:" << pixeis;

        float distancias[72];
        for(int x = 5; x < 77;x++)
        {
            distancias[x-5] = recebido.at(x).toFloat();
        }
        obstaculosPaint(distancias);
    }
}

void MainWindow::on_btClear_clicked()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_bt_ballPosition_clicked()
{
    /*QStringList recebidoBola = ui->tbFile->text().split(",");
    float distanciaBola = recebidoBola.at(0).toFloat()*100;
    float anguloBola = recebidoBola.at(1).toFloat();
    float pixeis = distanciaBola*8/10;



    float y = sin((360-anguloRobo+anguloBola)*(1/57.3))*pixeis;
    float x = cos((360-anguloRobo+anguloBola)*(1/57.3))*pixeis;

    qDebug() << "anguloBola: " << anguloBola << " pixeis:" << pixeis;

    //qDebug() << "X: " << x << " Y:" << y;
    ball1->setPos((robo1->pos().x()+robo1->width/2)+x,(robo1->pos().y()+robo1->height/2)+y);*/

    QString aux = ui->tbFile->text();
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
    ui->plainTextEdit->appendPlainText(" Angulo: "+QString::number(anguloRobo));
    robo1->setPos(xReal-(robo1->width/2),yReal-(robo1->height/2));
    robo1->setAngle(anguloRobo);


    float distanciaBola = recebido.at(3).toFloat()*100;
    float anguloBola = recebido.at(4).toFloat();
    float pixeis = distanciaBola*8/10;

    float offset = 11;
    float anguloOfsset = (anguloBola-offset);
    if(anguloOfsset<0)
    {
        anguloOfsset = anguloOfsset+360;
    }

    float y = sin((360-anguloRobo+anguloOfsset)*(1/57.3))*pixeis;
    float x = cos((360-anguloRobo+anguloOfsset)*(1/57.3))*pixeis;

    //qDebug() << "anguloBola: " << anguloBola << " pixeis:" << pixeis;

    //qDebug() << "X: " << x << " Y:" << y;
    ball1->setPos((robo1->pos().x()+robo1->width/2)+x,(robo1->pos().y()+robo1->height/2)+y);
}

void MainWindow::on_bt_osbt_clicked()
{


    /*int number = 0;
    float mediadist = 0;
    float mediaangulo = 0;
    for(int y=0;y<72;y++)
    {
        if(dist[y] != 0)
        {
            mediadist += dist[y];
            mediaangulo += y;
            number++;
        }
    }
    mediadist = mediadist/number;
    mediaangulo = mediaangulo/number;
    qDebug() << "Media: " << mediadist << " Angulo" << mediaangulo;

    mediadist = mediadist*80; //metros para pixeis

    obs->setSize(dist);

    float offset = 11;
    float anguloOfsset = (mediaAngulo-offset);
    float y = sin((360-anguloRobo+anguloOfsset)*(1/57.3))*mediaDist;
    float x = cos((360-anguloRobo+anguloOfsset)*(1/57.3))*mediaDist;
    obts->setPos((robo1->pos().x()+robo1->width/2)+x,(robo1->pos().y()+robo1->height/2)+y);

    qDebug() << "X: " << x << " Y" << y;*/
}

bool MainWindow::obstaculosPaint(float dist[])
{
    for(int u=0;u<36;u++)
    {
        if(obstaculos[u]->isActive())
        {
            scene->removeItem(obstaculos[u]);
        }
    }


    //Dummy
    /*float dist[72];
    for(int y=0;y<72;y++)
    {
        dist[y] = 0;
    }
    dist[1] = 1.5;
    dist[2] = 1.6;

    dist[35] = 1.5;
    dist[36] = 1.6;
    dist[71] = 1.6;*/

    float auxMediaDist = 0;
    float auxMediaAngulo = 0;
    int aux = 0;
    bool obstdetected = false;
    float distaux[72];

    int obstnumero = 0;
    for(int y=0;y<72;y++)
    {
        aux = 0;
        while(dist[y] != 0 && y<72)
        {
           auxMediaDist += dist[y];
           auxMediaAngulo += y;
           distaux[aux] = dist[y];
           aux ++;
           y++;
           obstdetected = true;
        }
        if(obstdetected)
        {
            auxMediaDist = auxMediaDist/aux;
            auxMediaAngulo = auxMediaAngulo/aux;
            scene->addItem(obstaculos[obstnumero]);

            auxMediaDist = auxMediaDist*80;
            auxMediaAngulo = auxMediaAngulo*5;

            obstaculos[obstnumero]->setSize(distaux);

            qDebug() << "anguloRobo: " << anguloRobo << "Gajo: " <<obstnumero <<"auxMediaAngulo: " << auxMediaAngulo;
            float y = sin(360-(anguloRobo+(auxMediaAngulo+220))*(1/57.3))*auxMediaDist; //1/57.3 to rad
            float x = cos(360-(anguloRobo+(auxMediaAngulo+220))*(1/57.3))*auxMediaDist;
            obstaculos[obstnumero]->setPos((robo1->pos().x()+robo1->width/2)+x,(robo1->pos().y()+robo1->height/2)+y);
            obstnumero++;

        }
        obstdetected = false;
        for(int k=0;k<72;k++)
        {
            distaux[k] = 0;
        }
        auxMediaDist = 0;
        auxMediaAngulo = 0;
    }
}


