#ifndef DIMENSIONS_H
#define DIMENSIONS_H
#include "mesures.h"

class Dimensions : public Mesures
{
public:
    Dimensions(QString _nom ,
               QString _valeurs ,
               QString _nominale="" ,
               QString _toleranceSup="" ,
               QString _toleranceInf="" ,
               QString _ecart="");
    virtual QStringList textList();
    virtual float getToleranceSup();
    virtual float getToleranceInf();
    virtual float getEcart();
    virtual bool isToleranced();

private:
    QString nominale;
    QString toleranceSup , toleranceInf;
    QString ecart;
    bool tolerance;
    static bool pp;

};

#endif // DIMENSIONS_H
