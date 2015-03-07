#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool OnMove;
    void drawLine(int x1, int y1, int x2, int y2);
    ~MainWindow();
private slots:
    void initSocket();
    void readPendingDatagrams();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void updatePos();
    void on_bt_osbt_clicked();

    void on_btClear_2_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    float factor = 1.6;
    int anguloRobo = 0;
    QTimer *timerNewPos;
};

#endif // MAINWINDOW_H
