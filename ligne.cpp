#include "ligne.h"
#include <QPen>
#include <QMessageBox>
#include <QFocusEvent>
#include <QDebug>
#include <QPainter>
#include <QPaintEngine>


Ligne::Ligne( QString _name , bool _isEmpty, bool _title ) :
        ElemFocusable(_name , false , _title)
{
    isEmpty = _isEmpty;
    lh = 1;
	if(isEmpty)
		this->setPen(QPen(Qt::NoPen));
    if(Encart)
        this->setBrush(QColor(230,230,230));

	QGraphicsRectItem::setZValue(3);
}

void Ligne::print(QPainter *painter , int &y , QPrinter &printer){

    float scaleP = printer.paperRect().width()/A4_X;

	QPen pen(Qt::SolidLine);
	pen.setWidth(1);
	pen.setColor(QColor(Qt::black));

	painter->setPen(pen);
    painter->setBrush(QBrush(Qt::NoBrush));
	if(!isEmpty){
        if(y+LINE_HEIGHT*lh*scaleP > (A4_Y-MARGIN)*scaleP){
			printer.newPage();
            y = MARGIN * scaleP;

            ElemFocusable::currentPage++;
            painter->drawText((A4_X-8)*scaleP , (A4_Y-6)*scaleP , QString::number(ElemFocusable::currentPage));
            painter->setFont(QFont("Arial" , 6));
            painter->drawText((3*MARGIN)*scaleP , (A4_Y-6)*scaleP , "Rapport realisé sur une machine MicroVu");
            painter->setFont(QFont("Arial" , 8));
		}
        if(Encart)
            painter->setBrush(QBrush(QColor(230,230,230)));
        else if(GetName()[0]!='@'){
            painter->setBrush(QColor(238,236,225));
            painter->setPen(Qt::NoPen);
            float pas = (A4_X-2*MARGIN-14)/(6.8)*scaleP;
            float xr = (MARGIN+2)*scaleP + 1.6*pas;
            for(int i = 0 ; i < 2 ; i ++){
                painter->drawRect(xr,y,pas,lh*LINE_HEIGHT*scaleP);
                xr+=2*pas;
            }
            painter->drawRect(xr,y,(A4_X-MARGIN)*scaleP-xr,lh*LINE_HEIGHT*scaleP);
            painter->setPen(Qt::SolidLine);
            painter->setBrush(Qt::NoBrush);
        }
        painter->drawRect(MARGIN*scaleP,y ,(A4_X-2*MARGIN)*scaleP, LINE_HEIGHT*lh*scaleP);
	}

    y += LINE_HEIGHT*lh*scaleP;
    painter->setBrush(QBrush(Qt::NoBrush));
}

void Ligne::setScale(float scale){
    this->setRect(0,0,(A4_X-2*MARGIN)*scale , LINE_HEIGHT*scale*lh);
}
