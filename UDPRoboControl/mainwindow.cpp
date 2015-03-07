#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QHostAddress"
#include <QUdpSocket>
#include "joypad.h"


QUdpSocket *udpSocketOut;
QUdpSocket *udpSocketIn;

QString MyAddress = "192.168.1.115";
QString DestineAddress = "192.168.1.102";

int MyPort = 1235;
int DestinePort = 1234;

JoyPad *btJoy = new JoyPad();

int JoyMaxy = 150;
int JoyMaxx = 160;

int angle = 0;
int vel_max = 70;
int P_max = 150;
int V_obt = 0;

bool open_serial = false;

QString lido = "";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->cb_serial->addItem(info.portName());
    }
    ui->cb_baudrate->addItem("9600");
    ui->cb_baudrate->addItem("14400");
    ui->cb_baudrate->addItem("19200");
    ui->cb_baudrate->addItem("28800");
    ui->cb_baudrate->addItem("34800");
    ui->cb_baudrate->addItem("57600");
    ui->cb_baudrate->addItem("115200");
    ui->cb_baudrate->setCurrentIndex(5);

    sceneJoy = new QGraphicsScene(this);
    ui->graphicsViewJoy->setScene(sceneJoy);
    ui->graphicsViewJoy->setRenderHint(QPainter::Antialiasing);

    sceneJoy->setSceneRect(0,0,300,300);

    btJoy->setPos(JoyMaxx,JoyMaxy);
    sceneJoy->addItem(btJoy);

    QTimer *timerJoys = new QTimer(this);
    connect(timerJoys, SIGNAL(timeout()), this, SLOT(timeJoys()));
    timerJoys->start(17);

    initSocket();
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

void MainWindow::readPendingDatagrams()
{
    while (udpSocketIn->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketIn->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocketIn->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        ui->plainTextEdit->appendPlainText(datagram);
    }
}

void MainWindow::on_bt_send_clicked()
{
    Hello_UDP();
}

void MainWindow::Hello_UDP()
{
    QByteArray datagram;
    datagram.append("Hello I'm Acer");
    udpSocketOut->writeDatagram(datagram,QHostAddress(DestineAddress), DestinePort);
    //LIMIT 65,507 bytes (65,535 − 8 byte UDP header − 20 byte IP header)
}

void MainWindow::timeJoys()
{
    int joy0 = btJoy->x()-JoyMaxx;
    int joy1 = btJoy->y()-JoyMaxy;

    float rad = qAtan2(joy0,joy1);
    angle = ((rad*360)/(2*M_PI));
    if(angle<0)
    {
        angle = angle+360;
    }

    long int P_obt = 0;
    if(joy1!=0)
    {
        P_obt = qSqrt((joy1*joy1)+(joy0*joy0));
    }
    else
    {
        P_obt = 0;
    }
    if(P_obt>P_max)
    {
        P_obt = P_max;
    }

    V_obt = (P_obt*100)/P_max;
    int aux = (V_obt*vel_max)/100;
    V_obt = aux;

    if(joy1>0)
    {
        V_obt = V_obt*-1;
    }

    ui->lb_values->setText(QString::number(V_obt)+" |"+QString::number(angle)+" º");

    int valor = 0;
    valor = joy0*vel_max/160;
    if(valor>vel_max)
    {
        valor=vel_max;
    }
    else if(valor<-vel_max)
    {
        valor=-vel_max;
    }

    QByteArray datagram;
    datagram.append("A "+QString::number(-V_obt)+"!"+QString::number(valor)+"\n");
    udpSocketOut->writeDatagram(datagram,QHostAddress(DestineAddress), DestinePort);
}

void MainWindow::on_bt_open_clicked()
{
    openSerial();
}

void MainWindow::on_bt_close_clicked()
{
    closeSerial();
}

void MainWindow::on_bt_refresh_clicked()
{
    refreshSerial();
}

void MainWindow::on_bt_clear_clicked()
{
    ui->txt_receber->clear();
}


void MainWindow::openSerial()
{
    if(!open_serial)
    {
        QString name = ui->cb_serial->currentText();
        QString baudrate = ui->cb_baudrate->currentText();

        serial.setPortName(name);

        serial.setBaudRate(baudrate.toInt());

        if (serial.open(QIODevice::ReadWrite))
        {
            connect(&serial, SIGNAL(readyRead()),this, SLOT(readResponse()));

            QThread::sleep(6);

            serial.write("Hi");  // Say Hi

            open_serial = true;

            QMessageBox msgBox;
            msgBox.setText("Open!");
            msgBox.exec();

        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Erro: "+serial.errorString());
            msgBox.exec();
        }
    }
}

void MainWindow::closeSerial()
{
    if(serial.isOpen())
    {
        open_serial = false;
        serial.close();
        QMessageBox msgBox;
        msgBox.setText("Closed!");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Serial Port not open!");
        msgBox.exec();
    }
}

void MainWindow::refreshSerial()
{
    ui->cb_serial->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->cb_serial->addItem(info.portName());
    }
}

void MainWindow::readResponse()
{
    lido = serial.readAll();
    ui->txt_receber->appendPlainText(lido);
}

void MainWindow::on_bt_encoder_clicked()
{
    QByteArray datagram;
    datagram.append("M"+ui->ln_encoder->text()+"\n");
    udpSocketOut->writeDatagram(datagram,QHostAddress(DestineAddress), DestinePort);
}

void MainWindow::on_bt_encoder2_clicked()
{
    QByteArray datagram;
    datagram.append("N"+ui->ln_encoder_2->text()+"\n");
    udpSocketOut->writeDatagram(datagram,QHostAddress(DestineAddress), DestinePort);
}
