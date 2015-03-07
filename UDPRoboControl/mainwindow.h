#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void initSocket();

    void readPendingDatagrams();

    void on_bt_send_clicked();

    void Hello_UDP();

    void timeJoys();


    void on_bt_open_clicked();

    void on_bt_close_clicked();

    void on_bt_refresh_clicked();

    void on_bt_clear_clicked();

    void openSerial();

    void closeSerial();

    void refreshSerial();

    void readResponse();

    void on_bt_encoder_clicked();

    void on_bt_encoder2_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *sceneJoy;
    QSerialPort serial;
};

#endif // MAINWINDOW_H
