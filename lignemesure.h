#ifndef LIGNEMESURE_H
#define LIGNEMESURE_H
#include "lignetext.h"

class LigneMesure : public LigneText
{
private:
	float ecart , length , tolP,tolM;
	QGraphicsRectItem *box,*boxVal;
	QList<QGraphicsLineItem *> barres;
    int boxLength;
    bool center;

public:
    LigneMesure(Mesures *mesure ,QString name = "Mesure" );
	~LigneMesure();
    void print(QPainter *painter , int &y , QPrinter &printer);
    virtual void setScale(float scale);

};

#endif // LIGNEMESURE_H
