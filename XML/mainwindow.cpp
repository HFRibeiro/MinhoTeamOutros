#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    writeComponent();

    loadFile("componentes.xml");
    extractXmlData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile(QString FileName)
{
    // Load xml file as raw data
    QFile f(FileName);

    if (!f.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        qDebug() << "Error while loading file";
    }
    // Set data into the QDomDocument before processing
    xmlDOC.setContent(&f);
    f.close();
}

void MainWindow::extractXmlData()
{
    QPlainTextEdit *plainText = ui->plainTextEdit;
    /////////////////////////////////////////////////////////////

    // Extract the root markup
    QDomElement root = xmlDOC.documentElement();

    // Get root names and attributes
    QString Type = root.tagName();
    QString Board = root.attribute("BOARD","No name");
    int Year = root.attribute("YEAR","1900").toInt();

    // Display root data
    /*qDebug() << "Type  = " << Type.toStdString().c_str();
    qDebug() << "Board = " << Board.toStdString().c_str();
    qDebug() << "Year  = " << Year;*/

    plainText->appendPlainText("Type  = " + Type);
    plainText->appendPlainText("Board = " + Board);
    plainText->appendPlainText("Year  = " + QString::number(Year)+"\n");

    ///////////////////////////////////////////////////////////

    // Get the first child of the root (Markup COMPONENT is expected)
    QDomElement Component = root.firstChild().toElement();

    // Loop while there is a child
    while(!Component.isNull())
    {
        // Check if the child tag name is COMPONENT
        if (Component.tagName()=="COMPONENT")
        {
            // Read and display the component ID
            QString ID = Component.attribute("ID","No ID");

            // Get the first child of the component
            QDomElement Child = Component.firstChild().toElement();

            QString Name;
            double Value;

            // Read each child of the component node
            while (!Child.isNull())
            {
                // Read Name and value
                if (Child.tagName() == "NAME") Name = Child.firstChild().toText().data();
                if (Child.tagName() == "VALUE") Value = Child.firstChild().toText().data().toDouble();

                // Next child
                Child = Child.nextSibling().toElement();
            }

            // Display component data
            /*qDebug() << "Component " << ID.toStdString().c_str();
            qDebug() << "   Name  = " << Name.toStdString().c_str();
            qDebug() << "   Value = " << Value;*/

            plainText->appendPlainText("Component " + ID);
            plainText->appendPlainText("Name  = " + Name);
            plainText->appendPlainText("Value  = " + QString::number(Value)+"\n");
        }

        // Next component
        Component = Component.nextSibling().toElement();
    }
}

bool MainWindow::writeComponent()
{
    // Load xml file as raw data
    QFile output("componentes.xml");

    if (!output.open(QIODevice::ReadWrite | QFile::Text))
    {
        // Error while loading file
        qDebug() << "Error while loading file to Write";
    }
    // Set data into the QDomDocument before processing

    ///////////////////////
       streamWrite.setDevice(&output);
       streamWrite.setAutoFormatting(true);
       streamWrite.writeStartDocument();

       streamWrite.writeStartElement("ELEC");

       streamWrite.writeAttribute("BOARD", "Motor controller");
       streamWrite.writeAttribute("YEAR", "2015");

       streamWrite.writeStartElement("COMPONENT");

       streamWrite.writeAttribute("ID", "R1");
       streamWrite.writeTextElement("NAME", "RESITOR");
       streamWrite.writeTextElement("VALUE", "1.25");

       streamWrite.writeEndElement(); // COMPONENT

       streamWrite.writeEndElement(); // ELEC

       streamWrite.writeEndDocument();

       output.close();
}
