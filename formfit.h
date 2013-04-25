#ifndef FORMFIT_H
#define FORMFIT_H
#include "mesures.h"
#include <QStringList>


class FormFit : public Mesures
{
public:
    FormFit(QString _nom ,
            QString _valeurs ,
            QString _nominale="" ,
            QString _ecart="");
    virtual QStringList textList();

private:
    QString nominale;
    QString ecart;
};

#endif // FORMFIT_H
