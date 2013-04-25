#ifndef LOCALISATION_H
#define LOCALISATION_H
#include "mesures.h"
#include <QStringList>

class Localisation : public Mesures
{
public:
    Localisation(QString _nom ,
                 QString _valeurs ,
                 QString _zone="" ,
                 QString _devT="" ,
                 QString _xval="" ,
                 QString _yval="" ,
                 QString _xnom="" ,
                 QString _ynom="" );
                virtual QStringList textList();
    float getEcart();
    virtual bool isToleranced()
            {return true;}

    virtual float getToleranceSup()
            {return zone.toFloat();}

private:
    QString zone ,devT , xval , yval , xnom , ynom ;

            };
#endif // LOCALISATION_H
