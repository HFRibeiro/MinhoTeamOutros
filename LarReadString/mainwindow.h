#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

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
    void on_btPosition_clicked();
    bool readFile(QString FileName);
    void splitValues();
    int getPosition(QString distances);
    bool eventFilter(QObject *ob, QEvent *ev);

    void on_dial_sliderMoved(int position);

    void initSocket();

    void readPendingDatagrams();

    void on_btClear_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    float factor = 1.6;
};

#endif // MAINWINDOW_H
