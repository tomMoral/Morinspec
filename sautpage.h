#ifndef SAUTPAGE_H
#define SAUTPAGE_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QPrinter>
#include "mesures.h"
#include "elemlist.h"
#include "elemfocusable.h"

class SautPage : public ElemFocusable
{
    Q_OBJECT
private:

public:
    SautPage(QString _name = "Saut Page");
    virtual bool jump(){return true;}
    virtual void print(QPainter *painter, int &y, QPrinter &printer);
};

#endif // SAUTPAGE_H
