#include "lignecom.h"

LigneCom::LigneCom(QString _info ):
    Ligne(QString("@")+_info , false)
{
    infoText = _info;
    scale = SCALE;
    info = new QGraphicsTextItem(_info , this);
    QPointF pos((this->boundingRect().width()-info->boundingRect().width())/2 ,
                (this->boundingRect().height()-info->boundingRect().height())/2);
    info->setPos(pos);
}

LigneCom::~LigneCom(){
    delete this->info;
}

void LigneCom::print(QPainter *painter , int &y , QPrinter &printer){
    float scaleP = printer.paperRect().width()/A4_X;
    int y0 = y;
    QFont f = painter->font();

    Ligne::print(painter,y,printer);
    painter->setFont(font);
    if (y0 > y)
        y0 = (MARGIN+6)*scaleP;
    QRectF rect(MARGIN*scaleP,y0 ,(A4_X-2*MARGIN)*scaleP, LINE_HEIGHT*scaleP);
    painter->drawText(rect , infoText , QTextOption(Qt::AlignCenter));
    painter->setFont(f);

}

void LigneCom::setScale(float _scale){
    scale = _scale;
    Ligne::setScale(scale);
    QFont f = font;
    f.setPointSize(font.pointSize()*scale/3);
    info->setFont(f);
    info->setPos(QPointF((this->boundingRect().width()-info->boundingRect().width())/2 ,
                                  (this->boundingRect().height()-info->boundingRect().height())/2));
}

void LigneCom::setFont(QFont _font, int mode){
    if(mode != 0){
        int ps = this->font.pointSize();
        if(mode > 1){
            ps-= mode*2-5;
            _font.setFamily(this->font.family());
        }
        _font.setPointSize(ps);
    }
    _font.setBold(this->font.bold());
    font = _font;
    _font.setPointSize(_font.pointSize()*(this->scale/3));
    info->setFont(_font);
}
