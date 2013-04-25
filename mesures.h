#ifndef MESURES_H
#define MESURES_H
#include <QString>

class Mesures
{
public:
    Mesures(QString ligne);
    Mesures(QString _nom , QString _valeur);
    QString display();
    virtual QStringList textList();
    virtual bool isToleranced()
            {return false;}
    virtual float getEcart()
            {return 0;}
    virtual float getToleranceSup()
            {return 0;}
    virtual float getToleranceInf()
            {return 0;}
    virtual float getVal()
            {return valeur.toFloat();}

private:
    QString nom;
    QString valeur;
};

#endif // MESURES_H
