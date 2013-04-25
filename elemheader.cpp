#include "elemheader.h"
#include <QApplication>


ElemHeader::ElemHeader(float &_x, float &_y , QString _info , bool _logo  ):
    QGraphicsRectItem(_x,_y,10,10)
{
	moves = false;
	x = _x;
    y = _y;
    scaleRatio = 3;
	logo = _logo;
    info = _info;
    if(!logo){
        font = QApplication::font();
        tex = new  QGraphicsTextItem(info , this);
        pix = NULL;
        this->setRect(tex->boundingRect());
    }
    else{
        pix = new  QGraphicsPixmapItem(QPixmap(info).scaledToHeight((LINE_HEIGHT-1)*SCALE*3 , Qt::SmoothTransformation),this);
        tex = NULL;
        this->setRect(pix->boundingRect());
    }
    this->setPos(scaleRatio*x,scaleRatio*y);
    this->setPen(QPen(Qt::NoPen));
    if(logo)
        _x += this->boundingRect().width()/SCALE+1;
    else{
        _y += LINE_HEIGHT;
        if(_y > LINE_HEIGHT*3){
            _y = 2;
            _x += this->boundingRect().width()/scaleRatio+7;
        }
    }
}

ElemHeader::~ElemHeader(){
    delete pix;
    delete tex;
}

void ElemHeader::setFont(QFont _font , int mode){
    if(!logo){
        if(mode != 0){
            float ps = font.pointSize();
            if(mode >1){
                ps -= (mode*2-5);
                _font.setFamily(font.family());
            }
            _font.setPointSize(ps);
        }
        font = _font;
        _font.setPointSize(_font.pointSize()*(scaleRatio/3));
        tex->setFont(_font);
        this->setRect(tex->boundingRect());
    }
}

void ElemHeader::print(QPainter *painter , int offsetX , int offsetY , float scaleP){
    if(logo)
        painter->drawPixmap(x*scaleP + offsetX , y*scaleP+ offsetY , QPixmap(info).scaledToHeight((LINE_HEIGHT-1)*scaleP*3 , Qt::SmoothTransformation));
    else{
        QFont f1 = painter->font();
        painter->setFont(font);
        painter->drawText(x*scaleP +offsetX, this->gety()*scaleP +offsetY + painter->fontMetrics().height() , info);
        painter->setFont(f1);
    }
}

void ElemHeader::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event ){
    this->grabMouse();
    moves = true;
}
void ElemHeader::mousePressEvent ( QGraphicsSceneMouseEvent * event ){
    if(moves){
        this->ungrabMouse();
        moves = false;
    }
    QGraphicsRectItem::mousePressEvent(event);
}
void ElemHeader::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){
	if(moves){
		QPointF pos = event->pos() , lastPos = event->lastPos();
		qreal dx = pos.x()-lastPos.x();
		qreal dy = pos.y()-lastPos.y();
        x += dx/scaleRatio;
        y += dy/scaleRatio;
		this->moveBy(dx,dy);
	}
}
void ElemHeader::setSelected(bool selected){
    if(selected){
        this->setPen(QPen(Qt::red));
    }
    else{
        this->setPen(Qt::NoPen);
    }
}

void ElemHeader::setScale(float scale){
    this->scaleRatio = scale;
    if(logo){
        delete pix;
        pix = new  QGraphicsPixmapItem(QPixmap(info).scaledToHeight((LINE_HEIGHT-1)*scale*3 , Qt::SmoothTransformation),this);
        this->setRect(pix->boundingRect());
    }
    else{
        QFont f = font;
        f.setPointSize(f.pointSize()*(scale/3));
        tex->setFont(f);
        this->setRect(tex->boundingRect());
        this->setPos(x*scale , y *scale);
    }
}
