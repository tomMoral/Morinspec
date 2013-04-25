#ifndef LIGNE_H
#define LIGNE_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QPrinter>
#include "mesures.h"
#include "elemlist.h"
#include "elemfocusable.h"


class Ligne :public ElemFocusable
{

    Q_OBJECT
private:
    bool isEmpty;
    float lh;

public:
    Ligne(QString name = "New Ligne" , bool isEmpty = true, bool _title = false );

    virtual void print(QPainter *painter , int &y , QPrinter &printer);
    void setLh(float _lh){ lh = _lh;}
    float getLh() { return lh;}
    virtual void setScale(float scale);
    
};

#endif // LIGNE_H
