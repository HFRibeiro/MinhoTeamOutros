#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_bt_enviar_clicked();

    void on_bt_open_clicked();

    void on_bt_close_clicked();

    void readResponse();

    void on_bt_limpar_clicked();

    virtual void keyPressEvent(QKeyEvent *e);

    void on_refresh_bt_clicked();

    void on_Kick_clicked();

    void cabecalho(char ID);

    void send_trama(int num_bytes);

private:
    Ui::MainWindow *ui;

    QByteArray TRAMA;

    QByteArray frameToSend;
};

#endif // MAINWINDOW_H
