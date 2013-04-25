#include "sautpage.h"


SautPage::SautPage(QString _name) :
    ElemFocusable(_name , false , false){
    this->setRect(0,0,0,0);
    this->setPen(Qt::NoPen);

}


void SautPage::print(QPainter *painter, int &y, QPrinter &printer){

    float scaleP = printer.paperRect().width()/A4_X;

    if(y == MARGIN * scaleP )
        return;
    printer.newPage();
    y = MARGIN * scaleP;

    ElemFocusable::currentPage++;
    painter->drawText((A4_X-8)*scaleP , (A4_Y-6)*scaleP , QString::number(ElemFocusable::currentPage));
    painter->setFont(QFont("Arial" , 6));
    painter->drawText((3*MARGIN)*scaleP , (A4_Y-6)*scaleP , "Rapport realisé sur une machine MicroVu");
    painter->setFont(QFont("Arial" , 8));
}
