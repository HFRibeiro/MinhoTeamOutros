#ifndef DESENHARCAMPO_H
#define DESENHARCAMPO_H
#include <QGraphicsScene>

class DesenharCampo
{
public:
    DesenharCampo();
    void desenharLinhas(QGraphicsScene *scene, float ComprimentoCampo, float LarguraCampo, float espessuraLinhas, float RaioCentro, float LarguraPequenaArea, float ComprimentoPequenaArea, float LarguraGrandeArea, float ComprimentoGrandeArea, float Canto, float bolaCentral, float bolaPenalti, float distanciaPenalti, int WidthGraphs, float margemEsq);
};

#endif // DESENHARCAMPO_H
