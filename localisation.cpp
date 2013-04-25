#include "localisation.h"

Localisation::Localisation(QString _nom ,
                            QString _valeur ,
                            QString _zone ,
                            QString _devT ,
                            QString _xval ,
                            QString _yval ,
                            QString _xnom ,
                            QString _ynom ) :
    Mesures(_nom , _valeur)
{
    zone = _zone;
    devT = _devT;
    xval = _xval;
    yval = _yval;
    xnom = _xnom;
    ynom = _ynom;
    if(devT == "0.0000")
        devT = "";

}
QStringList Localisation::textList(){
    QStringList res = Mesures::textList();

   //res << QString("x : ") +  xval + " / " + xnom  + "\ny : " +  yval + " / " + ynom;
   res << " " << zone << " "  << devT;
    //res  << zone  << devT ;

    return res;
}

float Localisation::getEcart(){
    return Mesures::getVal();
}
