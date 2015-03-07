#include "desenharcampo.h"
#include <QGraphicsEllipseItem>
#include "math.h"
#include <QDebug>

DesenharCampo::DesenharCampo()
{
}

void DesenharCampo::desenharLinhas(QGraphicsScene *scene, float ComprimentoCampo, float LarguraCampo, float espessuraLinhas, float RaioCentro, float LarguraPequenaArea, float ComprimentoPequenaArea, float LarguraGrandeArea, float ComprimentoGrandeArea, float CantoRaio, float bolaCentralRaio, float bolaPenaltiRaio, float distanciaPenalti,int WidthGraphs,float margemEsq)
{

    qDebug() << bolaPenaltiRaio;
    QPen pen(QColor (255,255,255));
    pen.setWidth(espessuraLinhas);

    int NewZero = (-WidthGraphs/2+margemEsq);

    //Campo
    //scene->addRect(-(ComprimentoCampo+espessuraLinhas)/2,-(LarguraCampo+espessuraLinhas)/2,ComprimentoCampo+(espessuraLinhas),LarguraCampo+espessuraLinhas,pen);
    scene->addRect(NewZero,-(LarguraCampo+espessuraLinhas)/2,(ComprimentoCampo+espessuraLinhas)/2,LarguraCampo+espessuraLinhas,pen);

    //Baliza
    scene->addRect(NewZero+(ComprimentoCampo+espessuraLinhas)/2,-(160+espessuraLinhas)/2,40+espessuraLinhas,(160+espessuraLinhas),pen);

    //Linha MeioCampo
    //scene->addLine(0,-(LarguraCampo)/2,0,LarguraCampo/2,pen);

    //Circulo MeioCampo
    //scene->addEllipse(-(RaioCentro+espessuraLinhas),-(RaioCentro+espessuraLinhas),(RaioCentro+espessuraLinhas)*2,(RaioCentro+espessuraLinhas)*2,pen);

    QGraphicsEllipseItem *QMeio = new QGraphicsEllipseItem(NewZero-(RaioCentro+espessuraLinhas),-(RaioCentro+espessuraLinhas),(RaioCentro+espessuraLinhas)*2,(RaioCentro+espessuraLinhas)*2);
    int startAngle = -90*16;
    int endAngle = 90*16;
    QMeio->setStartAngle(startAngle);
    QMeio->setSpanAngle(endAngle - startAngle);
    QMeio->setPen(pen);
    scene->addItem(QMeio);


    //PequenaArea Direita
    scene->addRect(NewZero+(ComprimentoCampo/2-(LarguraPequenaArea+(espessuraLinhas/2))),-(ComprimentoPequenaArea+espessuraLinhas)/2,LarguraPequenaArea+espessuraLinhas,ComprimentoPequenaArea+espessuraLinhas,pen);

    //PequenaArea Esquerda
    //scene->addRect(-(ComprimentoCampo/2+espessuraLinhas/2),-(ComprimentoPequenaArea+espessuraLinhas)/2,LarguraPequenaArea+espessuraLinhas,ComprimentoPequenaArea+espessuraLinhas,pen);

    //GrandeArea Direita
    scene->addRect(NewZero+((ComprimentoCampo/2-(LarguraGrandeArea+(espessuraLinhas/2)))),-(ComprimentoGrandeArea+espessuraLinhas)/2,LarguraGrandeArea+espessuraLinhas,ComprimentoGrandeArea+espessuraLinhas,pen);

    //GrandeArea Esquerda
    //scene->addRect(-(ComprimentoCampo/2+espessuraLinhas/2),-(ComprimentoGrandeArea+espessuraLinhas)/2,LarguraGrandeArea+espessuraLinhas,ComprimentoGrandeArea+espessuraLinhas,pen);

    //CantoRaio BaixoEsquerda
    /*QGraphicsEllipseItem *QEsqrB = new QGraphicsEllipseItem(-(ComprimentoCampo/2)-(CantoRaio+espessuraLinhas*1.5),(LarguraCampo/2)-CantoRaio-(espessuraLinhas*0.5),CantoRaio*2+espessuraLinhas*2,CantoRaio*2+espessuraLinhas*2);
    int startAngle = 0;
    int endAngle = 90*16;
    QEsqrB->setStartAngle(startAngle);
    QEsqrB->setSpanAngle(endAngle - startAngle);
    QEsqrB->setPen(pen);
    scene->addItem(QEsqrB);
    //CantoRaio CimaEsquerda
    QGraphicsEllipseItem *QEsqrC = new QGraphicsEllipseItem(-(ComprimentoCampo/2)-(CantoRaio+espessuraLinhas*1.5),-((LarguraCampo/2)+CantoRaio+(espessuraLinhas*1.5)),CantoRaio*2+espessuraLinhas*2,CantoRaio*2+espessuraLinhas*2);
    startAngle = 360*16;
    endAngle = 270*16;
    QEsqrC->setStartAngle(startAngle);
    QEsqrC->setSpanAngle(endAngle - startAngle);
    QEsqrC->setPen(pen);
    scene->addItem(QEsqrC);*/
    //CantoRaio BaixoDir
    QGraphicsEllipseItem *QDirB = new QGraphicsEllipseItem(NewZero+((ComprimentoCampo/2)-(CantoRaio+espessuraLinhas*0.5)),(LarguraCampo/2)-CantoRaio-(espessuraLinhas*0.5),CantoRaio*2+espessuraLinhas*2,CantoRaio*2+espessuraLinhas*2);
    startAngle = 90*16;
    endAngle = 180*16;
    QDirB->setStartAngle(startAngle);
    QDirB->setSpanAngle(endAngle - startAngle);
    QDirB->setPen(pen);
    scene->addItem(QDirB);
    //CantoRaio CimaDireita
    QGraphicsEllipseItem *QDirC = new QGraphicsEllipseItem(NewZero+((ComprimentoCampo/2)-(CantoRaio+espessuraLinhas*0.5)),-((LarguraCampo/2)+CantoRaio+(espessuraLinhas*1.5)),CantoRaio*2+espessuraLinhas*2,CantoRaio*2+espessuraLinhas*2);
    startAngle = 180*16;
    endAngle = 270*16;
    QDirC->setStartAngle(startAngle);
    QDirC->setSpanAngle(endAngle - startAngle);
    QDirC->setPen(pen);
    scene->addItem(QDirC);
    //bolaCentralRaio
    QBrush brush(QColor(255,255,255));
    pen.setWidth(1);
    scene->addEllipse(NewZero+(-bolaCentralRaio),-bolaCentralRaio,bolaCentralRaio*2,bolaCentralRaio*2,pen,brush);
    //bolaPenaltiRaioEsq
    //scene->addEllipse(-(ComprimentoCampo/2-distanciaPenalti),-bolaPenaltiRaio*2,bolaPenaltiRaio*2,bolaPenaltiRaio*2,pen,brush);
    //bolaPenaltiRaioDir
    scene->addEllipse(NewZero+((ComprimentoCampo/2-distanciaPenalti)-bolaPenaltiRaio*2),-bolaPenaltiRaio,bolaPenaltiRaio*2,bolaPenaltiRaio*2,pen,brush);

}


