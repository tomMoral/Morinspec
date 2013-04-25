#include "elemfocusable.h"

int ElemFocusable::currentPage = 0;

ElemFocusable::ElemFocusable(QString _name , bool _Header , bool _Encart ) :
		QObject(),
		QGraphicsRectItem( 0 , 0 ,(A4_X-2*MARGIN)*SCALE , LINE_HEIGHT*SCALE)
{
    if(!_Header)
        this->setFlag(QGraphicsItem::ItemIsFocusable);
	name = _name;
	Header = _Header;
    Encart = _Encart;
    position = 0;
}

void ElemFocusable::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsRectItem::mousePressEvent(event);
    if(Header) return;
	setBrush(QBrush(QColor(171,202,235,125)));
	this->setFocus();
    this->setZValue(3);
    emit selectedItem(position);
}

void ElemFocusable::focusInEvent(QFocusEvent *event){
    if(Header) return;
	setBrush(QBrush(QColor(171,202,235,125)));
    this->setZValue(3);
    emit selectedItem(position);
}

void ElemFocusable::focusOutEvent(QFocusEvent *event){

    if(Header) return;
    if(!Encart)
        setBrush(QBrush(QColor(255,255,255,255)));
    else
        setBrush(QBrush(QColor(230,230,230)));
    this->setZValue(0);
    if(this->pen().style()==Qt::NoPen)
        this->setZValue(-1);

}

void ElemFocusable::addChild(QGraphicsItem *rpz){
	rpz->setParentItem(this);
	rpz->setPos(0,0);
	this->setRect(this->boundingRect().x(),this->boundingRect().y() ,this->boundingRect().width() , rpz->boundingRect().height());
}

void ElemFocusable::print(QGraphicsRectItem *page , int &y , float scale){
	setParentItem(page);
    setPos(scale*MARGIN , y);
	y += this->boundingRect().height();
}

void ElemFocusable::save(QTextStream &out , QString Can){
	out << name << endl;
}

void ElemFocusable::setScale(float scale){
    this->setRect(0,0,(A4_X-2*MARGIN)*scale , LINE_HEIGHT*scale);
}

void ElemFocusable::setPosition(int _position){
    position = _position;
}

