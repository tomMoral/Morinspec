#include "lignetext.h"

LigneText::LigneText(QStringList encart , QString _name , bool _title ):
        Ligne(_name , false , _title)
{
    int y0 = 1;
    int y1 = LINE_HEIGHT*SCALE/4;
    int x0 = 2*SCALE;
    float pas = (A4_X-2*MARGIN-14)/(6.8);
    bool bigger = false;
    scale = SCALE;

    representations.append(new QGraphicsTextItem(encart[0] , this));
    Texts << encart[0];
    representations.back()->moveBy(x0, y0);
    if(representations.back()->boundingRect().width() > 1.5*SCALE*pas){
        int i = encart.at(0).indexOf(QRegExp(":"))+1;
        if(i== 0)
            i = encart.at(0).indexOf(QRegExp("\\s") , encart[0].size()/2-5)+1;
        encart[0] = encart[0].insert( i , "\n");
        while(i+1 < encart[0].size() && encart[0][i+1] == ' ')
            encart[0].remove(i+1,1);
        if(i+1 == encart[0].size()){
            encart[0].remove(i,1);
        }
        else{
            this->setRect(this->boundingRect().x() , this->boundingRect().y() , this->boundingRect().width() , LINE_HEIGHT*SCALE*3/2);
            bigger = true;
            this->setLh(3/2.);
        }
        representations.back()->setPlainText(encart[0]);
        Texts.removeAt(0);
        Texts << encart[0];
    }
    x0+= 1.8*pas*SCALE;
    representations.append(new QGraphicsTextItem(encart[1] , this));
    Texts << encart[1];
    representations.back()->moveBy(x0, y0);
    if(representations.back()->boundingRect().height() > LINE_HEIGHT*SCALE && !bigger){
            this->setRect(this->boundingRect().x() , this->boundingRect().y() , this->boundingRect().width() , LINE_HEIGHT*SCALE*3/2);
            bigger = true;
            this->setLh(3/2.);
    }
    x0+= pas*SCALE;
    if(representations.back()->boundingRect().width() > SCALE*pas){
        x0 += SCALE*pas*0.25;
        representations.back()->moveBy(-pas*0.25*SCALE,0);

    }
    for (int i =2 ; i < encart.size() ; i++){
        representations <<  new QGraphicsTextItem(encart[i] , this);
        Texts << encart[i];
        representations.back()->moveBy(x0, y0);
        if(representations.at(i)->boundingRect().height() > LINE_HEIGHT*SCALE){
            this->setRect(this->boundingRect().x() , this->boundingRect().y() , this->boundingRect().width() , LINE_HEIGHT*SCALE*3/2);
            bigger = true;
            this->setLh(3/2.);

        }
        x0+= pas*SCALE;
    }
    if(bigger)
        for (int i =0 ; i < representations.size() ; i++){
            if(representations.at(i)->boundingRect().height() < LINE_HEIGHT*SCALE)
                representations.at(i)->moveBy(0 , y1);
        }
    if(!Encart)
        shading();

}

LigneText::~LigneText(){
    for(int i = 0 ; i < representations.size() ; i++)
        delete representations[i];
    for(int i = 0 ; i < shades.size() ; i++)
        delete shades[i];
}

void LigneText::print(QPainter *painter , int &y , QPrinter &printer){

    float scaleP = printer.paperRect().width()/A4_X;
    float x0 = (MARGIN+2)*scaleP;
    float y0 = y;
    float pas = (A4_X-2*MARGIN-14)/(6.8)*scaleP;
    float LineH= this->getLh()*LINE_HEIGHT*scaleP;
    float x1;
    QFont f = painter->font();

    Ligne::print(painter,y,printer);
    painter->setFont(font);
    if (y0 > y)
        y0 = MARGIN*scaleP;
    painter->drawText(QRectF(x0,y0,1.5*pas,LineH) , Qt::TextWordWrap | Qt::AlignVCenter,Texts[0]);
    x0+=1.8*pas;
    for(int i = 1 ; i < Texts.size() ; i++){
        x1 = x0;
        if(Texts[i].contains('\n'))
            x1 = x0-0.25*pas;
        painter->drawText(QRectF(x1,y0,pas,LineH) , Qt::TextWordWrap |Qt::AlignVCenter,Texts[i]);

        x0+=pas;
    }
    painter->setFont(f);
}

void LigneText::setFont(QFont _font, int mode){
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
    float x0 = 2*scale;
    float pas = (A4_X-2*MARGIN-14)/(6.8)*scale;
    representations[0]->setFont(_font);
    representations[0]->setPos(x0 ,(this->rect().height()-representations[0]->boundingRect().height())/2);
    x0+= 1.8*pas;
    for(int i = 1 ; i < representations.size() ; i++){
        representations[i]->setFont(_font);
        representations[i]->setPos(x0 ,(this->rect().height()-representations[i]->boundingRect().height())/2);
        x0 += pas;
    }
    if(!Encart){
        for(int i = 0 ; i < shades.size() ; i++)
            delete shades[i];
        shades.clear();
        shading();
    }
}

void LigneText::setBold(bool _bold){
    if(!Encart) return;
    this->font.setBold(_bold);
    QFont _font = font;
    _font.setPointSize(_font.pointSize()*scale/3);
    float x0 = 2*scale;
    float pas = (A4_X-2*MARGIN-14)/(6.8)*scale;
    representations[0]->setFont(_font);
    representations[0]->setPos(x0 ,(this->rect().height()-representations[0]->boundingRect().height())/2);
    x0+= 1.8*pas;
    for(int i = 1 ; i < representations.size() ; i++){
        representations[i]->setFont(_font);
        representations[i]->setPos(x0 ,(this->rect().height()-representations[i]->boundingRect().height())/2);
        x0 += pas;
    }
    if(!Encart){
        for(int i = 0 ; i < shades.size() ; i++)
            delete shades[i];
        shades.clear();
        shading();
    }
}

void LigneText::setScale(float _scale){

    scale = _scale;
    Ligne::setScale(scale);
    QFont f = font;
    f.setPointSize(font.pointSize()*(scale/3));
    float x0 = 2*scale;
    float pas = (A4_X-2*MARGIN-14)/(6.8)*scale;
    representations[0]->setFont(f);
    representations[0]->setPos(x0 ,(this->rect().height()-representations[0]->boundingRect().height())/2);
    x0+= 1.8*pas;
    for(int i = 1 ; i < representations.size() ; i++){
        representations[i]->setFont(f);
        representations[i]->setPos(x0 ,(this->rect().height()-representations[i]->boundingRect().height())/2);
        x0 += pas;
    }
    if(!Encart){
        for(int i = 0 ; i < shades.size() ; i++)
            delete shades[i];
        shades.clear();
        shading();
    }

}

void LigneText::shading(){
    float pas = (A4_X-2*MARGIN-14)/(6.8)*scale;
    for(int i = 0 ; i < 2 ; i++){
        shades << new QGraphicsRectItem((2*i+1.6)*pas , 1,pas , this->boundingRect().height()-2,this);
        shades.back()->setPen(Qt::NoPen);
        shades.back()->setBrush(QColor(238,236,225));
        shades.back()->setZValue(-10);
    }
    shades << new QGraphicsRectItem(5.6*pas , 1,(A4_X-2*MARGIN)*scale-5.6*pas-1 , this->boundingRect().height()-2,this);
    shades.back()->setPen(Qt::NoPen);
    shades.back()->setBrush(QColor(238,236,225));
    shades.back()->setZValue(-10);
}
