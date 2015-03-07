#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QIODevice>
#include <QDataStream>
#include <QDir>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>

using namespace cv;
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
    void on_tr_Ymin_actionTriggered(int action);

    void on_tr_Ymax_actionTriggered(int action);

    void on_tr_Umin_actionTriggered(int action);

    void on_tr_Umax_actionTriggered(int action);

    void on_tr_Vmin_actionTriggered(int action);

    void on_tr_Vmax_actionTriggered(int action);

    void saveOption();

    void readOption();

    void on_bt_save_clicked();

    void on_bt_read_clicked();

    void processFrame();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    VideoCapture source;
    Mat image,processed,mask,mask2;
    QGraphicsScene *scene;
    QGraphicsPixmapItem* pixmapItem;
    int Y_min, Y_max, U_min, U_max, V_min, V_max;
};

#endif // MAINWINDOW_H
