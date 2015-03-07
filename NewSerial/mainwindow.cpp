#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>

QSerialPort serial;

//TRAMAS
#define HEADER_LAR1                     'L'
#define HEADER_LAR2                     'A'
#define HEADER_LAR3                     'R'
#define ID_KICK_H			0x23		//DataSize = 1 => Activa Chuto Horizontal
#define ID_KICK_V			0x24		//DataSize = 1 => Activa Chuto Vertical

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
}

MainWindow::~MainWindow()
{
    serial.close();
    delete ui;
}

void MainWindow::on_bt_enviar_clicked()
{
    if(serial.isOpen())
    {
        QByteArray char_array = ui->txt_enviar->text().toLocal8Bit();
        char *lido = char_array.data();
        serial.write(lido);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Open Serial Port First!");
        msgBox.exec();
    }
}

void MainWindow::on_bt_open_clicked()
{
    QString name = ui->cb_serial->currentText();
    QString baudrate = ui->cb_baudrate->currentText();

    serial.setPortName(name);

    serial.setBaudRate(baudrate.toInt());

    if (serial.open(QIODevice::ReadWrite))
    {
        connect(&serial, SIGNAL(readyRead()),this, SLOT(readResponse()));
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

void MainWindow::readResponse()
{
    ui->txt_receber->appendPlainText(serial.readAll());
}


void MainWindow::on_bt_close_clicked()
{
    if(serial.isOpen())
    {
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


void MainWindow::on_bt_limpar_clicked()
{
    ui->txt_receber->clear();
}


void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Enter:
        on_bt_enviar_clicked();
        break;
    case Qt::Key_Return:
        on_bt_enviar_clicked();
        break;
    default:

        break;
    }
}

void MainWindow::send_trama(int num_bytes)
{
    frameToSend.append(TRAMA);
    serial.write(frameToSend,num_bytes);
    frameToSend.clear();
}

void MainWindow::on_refresh_bt_clicked()
{
    ui->cb_serial->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->cb_serial->addItem(info.portName());
    }
}

void MainWindow::on_Kick_clicked()
{
    cabecalho(ID_KICK_V);

    //Kick Intensity
    TRAMA.insert(4, 20);

    //Send Frame
    send_trama(5);
}

void MainWindow::cabecalho(char ID)
{
    TRAMA.clear();

    TRAMA.insert(0, HEADER_LAR1);
    TRAMA.insert(1, HEADER_LAR2);
    TRAMA.insert(2, HEADER_LAR3);
    TRAMA.insert(3, ID);
}


