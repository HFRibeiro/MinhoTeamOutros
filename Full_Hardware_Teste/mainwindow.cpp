#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"
#include "myitem.h"
#include "backbutton.h"
#include "hat.h"
#include "textitem.h"
#include "joypad.h"

#include <QMessageBox>
//Windows
//#include "SDL/SDL.h"
//Ubuntu
#include "SDL2/SDL.h"
#include <QThread>
#include <math.h>

#include <QFile>
#include <QTextStream>
#include <QFileDialog>

GLWidget *wid;
QString lido = "";

JoyPad *btJoy = new JoyPad();

MyItem *bt1 = new MyItem();
MyItem *bt2 = new MyItem();
MyItem *bt3 = new MyItem();
MyItem *bt4 = new MyItem();

BackButton *bt5 = new BackButton();
BackButton *bt6 = new BackButton();
BackButton *bt7 = new BackButton();
BackButton *bt8 = new BackButton();

Hat *hat1 = new Hat();
Hat *hat2 = new Hat();
Hat *hat3 = new Hat();
Hat *hat4 = new Hat();

TextItem *txt1 = new TextItem();

SDL_Joystick *joystick;

bool bt1_click = false;
bool bt2_click = false;
bool bt3_click = false;
bool bt4_click = false;
bool bt5_click = false;
bool bt6_click = false;
bool bt7_click = false;
bool bt8_click = false;
bool bt9_click = false;
bool bt10_click = false;

bool hat1_click = false;
bool hat2_click = false;
bool hat3_click = false;
bool hat4_click = false;

int percent0 = 0;
int percent1 = 0;
int percent2 = 0;
int percent3 = 0;

QTimer *timerBt2;
int temp_bt2 = 0;
QTimer *timerBt3;
int temp_bt3 = 0;
QTimer *timerBt8;
int temp_bt8 = 0;

bool open_serial = false;
bool close_serial = false;

int angle = 0;
int vel_max = 40;
int P_max = 150;
int V_obt = 0;

int JoyMaxy = 150;
int JoyMaxx = 160;


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

    wid = ui->widget;

    scene = new QGraphicsScene(this);
    sceneJoy = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->graphicsViewJoy->setScene(sceneJoy);
    ui->graphicsViewJoy->setRenderHint(QPainter::Antialiasing);

    /*QMessageBox msgBox;
    msgBox.setText(QString::number(ui->graphicsView->width()));
    msgBox.exec();*/
    scene->setSceneRect(0,0,578,320);
    sceneJoy->setSceneRect(0,0,300,300);

    btJoy->setPos(JoyMaxx,JoyMaxy);
    sceneJoy->addItem(btJoy);

    bt1->setNumber(QString::number(1));
    bt1->setPos(340,128);
    scene->addItem(bt1);
    bt2->setNumber(QString::number(2));
    bt2->setPos(365,153);
    scene->addItem(bt2);
    bt3->setNumber(QString::number(3));
    bt3->setPos(390,128);
    scene->addItem(bt3);
    bt4->setNumber(QString::number(4));
    bt4->setPos(365,102);
    scene->addItem(bt4);


    bt5->setNumber(QString::number(5));
    bt5->setPos(155,52);
    scene->addItem(bt5);
    bt6->setNumber(QString::number(6));
    bt6->setPos(360,52);
    scene->addItem(bt6);

    bt7->setNumber(QString::number(7));
    bt7->setPos(160,32);
    scene->addItem(bt7);
    bt8->setNumber(QString::number(8));
    bt8->setPos(355,32);
    scene->addItem(bt8);

    hat1->setTransparent();
    scene->addItem(hat1);

    txt1->setPos(255,10);
    txt1->setNumber("OFF");
    scene->addItem(txt1);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    timer->start(17);//60fps

    if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize SDL");
        msgBox.exec();
    }

    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);

    /*QMessageBox msgBox;
    msgBox.setText(QString::number(SDL_JoystickNumAxes (joystick)));
    msgBox.exec();

    msgBox.setText(SDL_JoystickName(joystick));
    msgBox.exec();*/

   QTimer *timerGamepad = new QTimer(this);
   connect(timerGamepad, SIGNAL(timeout()), this, SLOT(updateGamepad()));
   timerGamepad->start(17);

   QTimer *timerSerial = new QTimer(this);
   connect(timerSerial, SIGNAL(timeout()), this, SLOT(updateSerial()));
   timerSerial->start(100);


   timerBt2 = new QTimer(this);
   connect(timerBt2, SIGNAL(timeout()), this, SLOT(TimeBt2()));
   timerBt3 = new QTimer(this);
   connect(timerBt3, SIGNAL(timeout()), this, SLOT(TimeBt3()));
   timerBt8 = new QTimer(this);
   connect(timerBt8, SIGNAL(timeout()), this, SLOT(TimeBt8()));

   QTimer *timerJoys = new QTimer(this);
   connect(timerJoys, SIGNAL(timeout()), this, SLOT(timeJoys()));
   timerJoys->start(17);


   read_Files();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bt_open_clicked()
{
    openSerial();
}

void MainWindow::on_bt_close_clicked()
{
    closeSerial();
}

void MainWindow::on_refresh_bt_clicked()
{
   refreshSerial();
}

void MainWindow::readResponse()
{
    lido = serial.readAll();
    ui->txt_receber->appendPlainText(lido);
    /*lido += serial.readAll();
    if(lido.contains("?") && lido.contains("!"))
    {
        lido = lido.replace("!","");
        lido = lido.replace("?","");
        QStringList pieces = lido.split(",");
        ui->txt_receber->appendPlainText(lido);
        ui->tb_yaw_2->setText(pieces[0]);
        ui->tb_pitch_2->setText(pieces[1]);
        ui->tb_roll_2->setText(pieces[2]);
        wid->setYPR(pieces[0].toFloat(),pieces[1].toFloat(),pieces[2].toFloat());
        lido = "";
    }*/
}

void MainWindow::on_bt_clear_clicked()
{
    ui->txt_receber->clear();
}

void MainWindow::on_bt_setRot_2_clicked()
{
    updateRotation();
}

void MainWindow::updateRotation()
{
    float Yaw = ui->tb_yaw_2->text().toFloat();
    float Pitch = ui->tb_pitch_2->text().toFloat();
    float Roll = ui->tb_roll_2->text().toFloat();

    wid->setYPR(Yaw,Pitch,Roll);
}


void MainWindow::on_bt_calibrate_clicked()
{
    float Yaw = ui->tb_yaw_2->text().toFloat();
    float Pitch = ui->tb_pitch_2->text().toFloat();
    float Roll = ui->tb_roll_2->text().toFloat();

    wid->setYPROffset(Yaw,Pitch,Roll);
}

void MainWindow::updateGamepad()
{
    SDL_JoystickUpdate();
    check_buttons();
    int joy0 = SDL_JoystickGetAxis(joystick,2);
    int joy1 = SDL_JoystickGetAxis(joystick,3);
    int joy2 = SDL_JoystickGetAxis(joystick,0);
    int joy3 = SDL_JoystickGetAxis(joystick,1);
    ui->LjoyX->setValue(joy0);
    ui->LjoyY->setValue(joy1);
    ui->RjoyX->setValue(joy2);
    ui->RjoyY->setValue(joy3);

    int hat = SDL_JoystickGetHat(joystick,0);
    check_hat(hat);

    percent0 = (joy0*vel_max)/32767;
    percent1 = (joy1*vel_max)/32767;
    percent2 = (joy2*vel_max)/32767;
    percent3 = (joy3*vel_max)/32767;

    float rad = qAtan2(-joy0,-joy1);
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

    ui->label->setText(QString::number(V_obt)+" |"+QString::number(angle)+" º");
}

void MainWindow::check_buttons()
{
    //BT1/////////////////////////////////////////
    if(SDL_JoystickGetButton(joystick,0))//bt1_click
    {
        bt1->setclicked();
        update();
        bt1_click = false;
    }
    else if(!SDL_JoystickGetButton(joystick,0) && !bt1_click)
    {
        bt1->setNotclicked();
        update();
        bt1_click = true;
    }
    ////////////////////////////////////////////
    //BT2/////////////////////////////////////////
    if(SDL_JoystickGetButton(joystick,1))
    {
        bt2->setclicked();
        update();
        bt2_click = false;
        timerBt2->start(1);
    }
    else if(!SDL_JoystickGetButton(joystick,1) && !bt2_click)
    {
        bt2->setNotclicked();
        update();
        bt2_click = true;
        timerBt2->stop();
        if(serial.isOpen())
        {
            QString aString = "KH"+QString::number(temp_bt2)+"\n";
            QByteArray ba = aString.toUtf8();
            serial.write(ba);
        }
        ui->lb_horizontal->setText("PressedH: "+QString::number(temp_bt2));
        temp_bt2 = 0;
    }
    ////////////////////////////////////////////
    //BT3/////////////////////////////////////////
    if(SDL_JoystickGetButton(joystick,2))
    {
        bt3->setclicked();
        update();
        bt3_click = false;
        timerBt3->start(1);
    }
    else if(!SDL_JoystickGetButton(joystick,2) && !bt3_click)
    {
        bt3->setNotclicked();
        update();
        bt3_click = true;
        timerBt3->stop();
        if(serial.isOpen())
        {
            QString aString = "KV"+QString::number(temp_bt3)+"\n";
            QByteArray ba = aString.toUtf8();
            serial.write(ba);
        }
        ui->lb_vertical->setText("PressedV: "+QString::number(temp_bt3));
        temp_bt3 = 0;
    }
    ////////////////////////////////////////////
    //BT4/////////////////////////////////////////
    if(SDL_JoystickGetButton(joystick,3))
    {
        bt4->setclicked();
        update();
        bt4_click = false;
    }
    else if(!SDL_JoystickGetButton(joystick,3) && !bt4_click)
    {
        bt4->setNotclicked();
        update();
        bt4_click = true;
    }
    ////////////////////////////////////////////
    //BT5/////////////////////////////////////////
    if(SDL_JoystickGetButton(joystick,4) && bt5_click)
    {
        bt5->setclicked();
        update();
        bt5_click = false;
    }
    else if(!SDL_JoystickGetButton(joystick,4) && !bt5_click)
    {
        bt5->setNotclicked();
        update();
        if(serial.isOpen())
        {
            QString aString = "S\n";
            QByteArray ba = aString.toUtf8();
            serial.write(ba);
        }
        bt5_click = true;
    }
    ////////////////////////////////////////////
    //BT6/////////////////////////////////////////
    if(SDL_JoystickGetButton(joystick,5) && bt6_click)
    {
        bt6->setclicked();
        update();
        if(serial.isOpen())
        {
            QString aString = "D\n";
            QByteArray ba = aString.toUtf8();
            serial.write(ba);
        }
        bt6_click = false;
    }
    else if(!SDL_JoystickGetButton(joystick,5) && !bt6_click)
    {
        bt6->setNotclicked();
        update();
        bt6_click = true;
    }
    ////////////////////////////////////////////
    //BT7/////////////////////////////////////////
    if(SDL_JoystickGetButton(joystick,6))
    {
        bt7->setclicked();
        update();
        bt7_click = false;
    }
    else if(!SDL_JoystickGetButton(joystick,6) && !bt7_click)
    {
        bt7->setNotclicked();
        update();
        bt7_click = true;
    }
    ////////////////////////////////////////////
    //BT8/////////////////////////////////////////
    if(SDL_JoystickGetButton(joystick,7))
    {
        bt8->setclicked();
        update();
        bt8_click = false;
        timerBt8->start(1);
    }
    else if(!SDL_JoystickGetButton(joystick,7) && !bt8_click)
    {
        bt8->setNotclicked();
        update();
        bt8_click = true;
        timerBt8->stop();
        if(serial.isOpen())
        {
            QString aString = "KV"+QString::number(temp_bt8)+"\n";
            QByteArray ba = aString.toUtf8();
            serial.write(ba);
        }
        ui->lb_vertical->setText("PressedV: "+QString::number(temp_bt8));
        temp_bt8 = 0;
    }
    ////////////////////////////////////////////
    //BT9/////////////////////////////////////////
    if(SDL_JoystickGetButton(joystick,8))
    {
        //bt9->setclicked();
        update();
        bt9_click = false;
        closeSerial();
    }
    else if(!SDL_JoystickGetButton(joystick,8) && !bt9_click)
    {
        //bt9->setNotclicked();
        update();
        bt9_click = true;
        close_serial = false;

    }
    ////////////////////////////////////////////
    //BT10/////////////////////////////////////////
    if(SDL_JoystickGetButton(joystick,9))
    {
        //bt10->setclicked();
        update();
        bt10_click = false;
        openSerial();
    }
    else if(!SDL_JoystickGetButton(joystick,9) && !bt10_click)
    {
        //bt10->setNotclicked();
        update();
        bt10_click = true;
        open_serial = false;
    }
    ////////////////////////////////////////////
}

void MainWindow::check_hat(int value)
{
    switch(value)
    {
        case 1:
        //Top
        hat1->setVisible();
        hat1->setPos(170,125);
        hat1->setRotation(180);
        break;
        case 3:
        //Top-Right
        hat1->setVisible();
        hat1->setPos(185,125);
        hat1->setRotation(225);
        break;
        case 2:
        //Right
        hat1->setVisible();
        hat1->setPos(190,140);
        hat1->setRotation(270);
        break;
        case 6:
        //Bottom-Right
        hat1->setVisible();
        hat1->setPos(185,155);
        hat1->setRotation(315);
        break;
        case 4:
        //Bottom
        hat1->setVisible();
        hat1->setPos(170,155);
        hat1->setRotation(0);
        break;
        case 12:
        //Bottom-Left
        hat1->setVisible();
        hat1->setPos(155,155);
        hat1->setRotation(45);
        break;
        case 8:
        //Left
        hat1->setVisible();
        hat1->setPos(150,140);
        hat1->setRotation(90);
        break;
        case 9:
        //Left-Top
        hat1->setVisible();
        hat1->setPos(155,125);
        hat1->setRotation(135);
        break;
        default:
        hat1->setTransparent();
        break;

    }
    update();
}

void MainWindow::updateSerial()
{
    if(serial.isOpen())
    {
        QString aString = "A "+QString::number(percent1)+"!"+QString::number(percent2)+"\n";
        QByteArray ba = aString.toUtf8();
        serial.write(ba);
         /*QString bString = "B "+QString::number(angle)+"!"+QString::number(V_obt)+"\n";
         QByteArray bb = bString.toUtf8();
         serial.write(bb);*/
    }
}

void MainWindow::TimeBt2()
{
    temp_bt2++;
}

void MainWindow::TimeBt3()
{
    temp_bt3++;
}

void MainWindow::TimeBt8()
{
    temp_bt8++;
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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    update();
    QWidget::resizeEvent(event);
}

void MainWindow::on_verticalSliderKick_actionTriggered(int action)
{
    Q_UNUSED(action);
    ui->lb_kick->setText(QString::number(ui->verticalSliderKick->value())+"%");
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

    ui->lb_values->setText(QString::number(V_obt)+" |"+QString::number(angle)+" º");
    //ui->lb_values->setText(QString::number(btJoy->x()-JoyMaxx)+";"+QString::number(btJoy->y()-JoyMaxy));
}

void MainWindow::read_Files()
{

        QFile file(":/ArduinoV1.txt");
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }

        QTextStream in(&file);

        while(!in.atEnd()) {
            QString line = in.readLine();
            //QMessageBox::information(0, "",line);
            ui->codeArduino->appendPlainText(line);
        }
        file.close();

        //////////////////////////////////////////////////////////////////
        file.setFileName(":/Ir.txt");
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }

        in.setDevice(&file);

        while(!in.atEnd()) {
            QString line = in.readLine();
            //QMessageBox::information(0, "",line);
            ui->codeIr->appendPlainText(line);
        }
        file.close();

}

void MainWindow::on_bt_copiar_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save PDE File"), "",tr("PDE File (*.pde);"));

    QString Path = fileName;
    int x = Path.lastIndexOf('/');
    x++;
    Path.remove(x,Path.length()-x);

    QString MainName = fileName;
    MainName.replace(Path,"");
    MainName.remove(MainName.indexOf('.'),MainName.length());

    /*QMessageBox::information(0, "Path: ",Path);
    QMessageBox::information(0, "MainName: ",MainName);*/

    if (!QDir(Path+MainName).exists()) {
        QDir().mkdir(Path+MainName);
        Path+=(MainName+"/");
    }


    QFile file(":/ArduinoV1.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);

    QFile data(Path+MainName+".pde");
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        QString all = in.readAll();
        out << all;
    }

    file.close();
    data.close();

    //////////////////////////////////////////////////////////
    file.setFileName(":/Ir.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    in.setDevice(&file);

    data.setFileName(Path+"Ir"+".pde");
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        QString all = in.readAll();
        out << all;
    }

    file.close();
    data.close();

    QMessageBox::information(0, "Saved: ",Path);
}
