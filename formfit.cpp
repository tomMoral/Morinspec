#include "formfit.h"

FormFit::FormFit(QString _nom ,
        QString _valeur ,
        QString _nominale ,
        QString _ecart) :
    Mesures(_nom , _valeur)
{
    this->nominale = _nominale;
    this->ecart = _ecart;
}
QStringList FormFit::textList(){
    QStringList res = Mesures::textList();
    res << nominale  << ecart;

    return res;
}
