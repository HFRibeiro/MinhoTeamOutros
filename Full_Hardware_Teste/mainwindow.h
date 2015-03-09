#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>

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

    void on_bt_open_clicked();

    void on_bt_close_clicked();

    void on_refresh_bt_clicked();

    void readResponse();

    void on_bt_clear_clicked();

    void on_bt_setRot_2_clicked();

    void updateRotation();

    void on_bt_calibrate_clicked();

    void updateGamepad();
    void check_buttons();
    void check_hat(int value);

    void updateSerial();

    void TimeBt2();
    void TimeBt3();
    void TimeBt8();

    void timeJoys();

    void openSerial();
    void closeSerial();
    void refreshSerial();

    void resizeEvent(QResizeEvent *event);

    void on_verticalSliderKick_actionTriggered(int action);

    void read_Files();

    void on_bt_copiar_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort serial;
    QGraphicsScene *scene,*sceneJoy;
    QTimer *timer;
};

#endif // MAINWINDOW_H
