#include "dimensions.h"
#include <QStringList>
#include <QDebug>


bool Dimensions::pp = false;

Dimensions::Dimensions(QString _nom ,
                       QString _valeur ,
                       QString _nominale ,
                       QString _toleranceSup ,
                       QString _toleranceInf ,
                       QString _ecart) :
    Mesures(_nom , _valeur)
{
    this->nominale = _nominale;
    this->toleranceSup = _toleranceSup;
    this->toleranceInf = _toleranceInf;
    this->ecart = _ecart;
    this->tolerance = ((toleranceSup != "") || (toleranceInf != ""));

    float tS = toleranceSup.toFloat();
    float tI = toleranceInf.toFloat();
    if(tS*tI > 0)
        pp = true;
}

QStringList Dimensions::textList(){
    QStringList res = Mesures::textList();
    res << nominale;
    if(tolerance){
        res << toleranceSup;
        if(!pp)
            res << toleranceInf;
        else{
            if(toleranceInf.at(0) == '-')
                res << toleranceInf.remove(0,1);
            else
                res << QString("-") + toleranceInf;
        }
    }
    if(ecart.toFloat()!=0 )
        res << this->ecart;
    else if ( nominale == res[1] && !tolerance){
        res.pop_back();
    }

    return res;
}

float Dimensions::getToleranceSup()
{
    QString s = this->toleranceSup;
    bool ok;
    float res = s.toFloat(&ok);
    if(ok)
        return res;
    res = 0;
    QStringList angle = s.split(':');
    if(angle.size() == 3){
        float offset = 1;
        for(int i = 0 ; i < 3 ; i++){
            res += angle.at(i).toFloat()*offset;
            offset /= 60;
        }
    }
    return res;
}
float Dimensions::getToleranceInf()
{

    QString s = this->toleranceInf;
    bool ok = true;
    float res = s.toFloat(&ok);
    if(ok){
        if(!pp)
            return res;
        return -res;
    }
    res = 0;
    QStringList angle = s.split(':');
    if(angle.size() == 3){
        float offset = 1;
        for(int i = 0 ; i < 3 ; i++){
            res += angle.at(i).toFloat()*offset;
            offset /= 60;
        }
    }
    if(!pp)
        return res;
    return -res;
}
float Dimensions::getEcart()
{
    QString s = this->ecart;
    bool ok;
    float res = s.toFloat(&ok);
    if(ok)
        return res;
    res = 0;
    QStringList angle = s.split(':');
    if(angle.size() ==3){
        float offset = 1;
        for(int i = 0 ; i < 3 ; i++){
            res += angle.at(i).toFloat()*offset;
            offset /= 60;
        }
    }
    return res;
}
bool Dimensions::isToleranced(){
    return this->tolerance;
}
