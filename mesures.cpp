#include "mesures.h"
#include <QStringList>


Mesures::Mesures(QString ligne)
{
    nom = ligne;
}

Mesures::Mesures(QString _nom , QString _valeur)
{
    this->nom = _nom ;
    this->valeur = _valeur;
}

QString Mesures::display()
{
  return nom + "\t" + valeur ;
}
QStringList Mesures::textList(){
	QStringList res;
    res << nom << valeur ;
	return res;
}
