#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// Library needed for processing XML documents
#include <QtXml>
// Library needed for processing files
#include <QFile>
//Debug
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //The QDomDocument class represents an XML document.
    QDomDocument xmlDOC;

    QXmlStreamWriter streamWrite;

private slots :

    void loadFile(QString FileName);

    void extractXmlData();

    bool writeComponent();
};

#endif // MAINWINDOW_H
