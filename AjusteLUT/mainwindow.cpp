#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene;
    timer = new QTimer(this);

    source.open(0);

    ui->graphicsView->setScene(scene);

    connect(timer,SIGNAL(timeout()),this,SLOT(processFrame()));
    timer->start(33);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tr_Ymin_actionTriggered(int action)
{
    Q_UNUSED(action);
    ui->lbYmin->setText(QString::number(ui->tr_Ymin->value()));
    Y_min = ui->tr_Ymin->value();
}

void MainWindow::on_tr_Ymax_actionTriggered(int action)
{
    Q_UNUSED(action);
    ui->lbYMax->setText(QString::number(ui->tr_Ymax->value()));
    Y_max = ui->tr_Ymax->value();
}

void MainWindow::on_tr_Umin_actionTriggered(int action)
{
    Q_UNUSED(action);
    ui->lbUMin->setText(QString::number(ui->tr_Umin->value()));
    U_min = ui->tr_Umin->value();
}

void MainWindow::on_tr_Umax_actionTriggered(int action)
{
    Q_UNUSED(action);
    ui->lbUmax->setText(QString::number(ui->tr_Umax->value()));
    U_max = ui->tr_Umax->value();
}

void MainWindow::on_tr_Vmin_actionTriggered(int action)
{
    Q_UNUSED(action);
    ui->lbVMin->setText(QString::number(ui->tr_Vmin->value()));
    V_min = ui->tr_Vmin->value();
}

void MainWindow::on_tr_Vmax_actionTriggered(int action)
{
    Q_UNUSED(action);
    ui->lbVmax->setText(QString::number(ui->tr_Vmax->value()));
    V_max = ui->tr_Vmax->value();
}

void MainWindow::saveOption()
{
    QString Filename = "";
    if(ui->rb_campo->isChecked())
    {
        Filename = "campo.txt";
    }
    else if(ui->rb_linha->isChecked())
    {
        Filename = "linha.txt";
    }
    else if(ui->rb_bola->isChecked())
    {
        Filename = "bola.txt";
    }
    else
    {
        Filename = "obstaculo.txt";
    }

    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Save", "Save to "+Filename+"?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {

    QString min_Y = ui->lbYmin->text();
    QString max_Y = ui->lbYMax->text();

    QString min_U = ui->lbUMin->text();
    QString max_U = ui->lbUmax->text();

    QString min_V = ui->lbVMin->text();
    QString max_V = ui->lbVmax->text();


    QFile file;
    file.setFileName(Filename);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
            QMessageBox::information(0, "error", file.errorString());
    }


    QTextStream out(&file);

    out << "YMIN: "+min_Y << '\n';
    out << "YMAX: "+max_Y << '\n';

    out << "UMIN: "+min_U << '\n';
    out << "UMAX: "+max_U << '\n';

    out << "VMIN: "+min_V << '\n';
    out << "VMAX: "+max_V << '\n';

        file.close();

      } else {
      }
}

void MainWindow::readOption()
{
    QString Filename = "";
    if(ui->rb_campo->isChecked())
    {
        Filename = "campo.txt";
    }
    else if(ui->rb_linha->isChecked())
    {
        Filename = "linha.txt";
    }
    else if(ui->rb_bola->isChecked())
    {
        Filename = "bola.txt";
    }
    else
    {
        Filename = "obstaculo.txt";
    }
    QFile file;
    file.setFileName(Filename);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
            QMessageBox::information(0, "error", file.errorString());
    }


    QTextStream in(&file);

    int x = 0;
    while(!in.atEnd()) {
        QString line = in.readLine();
        if(x==0){
            QString val = line.remove("YMIN: ");
            ui->lbYmin->setText(val);
            ui->tr_Ymin->setValue(val.toInt());
            x++;
        }
        else if(x==1){
            QString val = line.remove("YMAX: ");
            ui->lbYMax->setText(val);
            ui->tr_Ymax->setValue(val.toInt());
            x++;
        }
        else if(x==2){
            QString val = line.remove("UMIN: ");
            ui->lbUMin->setText(val);
            ui->tr_Umin->setValue(val.toInt());
            x++;
        }
        else if(x==3){
            QString val = line.remove("UMAX: ");
            ui->lbUmax->setText(val);
            ui->tr_Umax->setValue(val.toInt());
            x++;
        }
        else if(x==4){
            QString val = line.remove("VMIN: ");
            ui->lbVMin->setText(val);
            ui->tr_Vmin->setValue(val.toInt());
            x++;
        }
        else if(x==5){
            QString val = line.remove("VMAX: ");
            ui->lbVmax->setText(val);
            ui->tr_Vmax->setValue(val.toInt());
            x++;
        }

    }

    file.close();
}

void MainWindow::on_bt_save_clicked()
{
    saveOption();
}

void MainWindow::on_bt_read_clicked()
{
    readOption();
}

void MainWindow::processFrame()
{
    if(source.isOpened()){
        source.read(image);
        //processa a cena
        cvtColor(image,processed,CV_RGB2YUV);
        inRange(processed,Scalar(ui->tr_Ymin->value(),ui->tr_Umin->value(),ui->tr_Vmin->value()),Scalar(ui->tr_Ymax->value(),ui->tr_Umax->value(),ui->tr_Vmax->value()),mask);
        QImage img(mask.data,mask.cols,mask.rows, mask.step,QImage::Format_Indexed8);

        pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(img));
        scene->clear();
        scene->addItem(pixmapItem);
    }
}
