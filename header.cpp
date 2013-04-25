#include "header.h"
#include <QPainter>
#include <QPrinter>
#include <QDebug>

Header::Header(QString _HeaderFile):
	ElemFocusable(_HeaderFile , true)
{
	this->setRect(0,0,(A4_X-2*MARGIN)*SCALE , 3*LINE_HEIGHT*SCALE );
    this->setBrush(QBrush(QColor(230,230,230)));

    this->setFlag(QGraphicsItem::ItemIsFocusable);
    selectedElem = -1;
}

void Header::add( ElemHeader* elem ){
    infos.push_back(elem);
}

void Header::print(QPainter *painter , int &y , QPrinter &printer){
    float scaleP = printer.paperRect().width()/A4_X;
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->setBrush(QBrush(QColor(230,230,230)));
    painter->drawRect(MARGIN*scaleP , y , (A4_X-2*MARGIN)*scaleP , LINE_HEIGHT*3*scaleP );
    painter->setBrush(Qt::NoBrush);
	for(int i = 0 ; i < infos.size() ; i++)
        infos[i]->print(painter , MARGIN*scaleP , y , scaleP);
    y +=  (LINE_HEIGHT*3+4)*scaleP;
}

void Header::print(QGraphicsRectItem *page , int &y, float scale){
	setParentItem(page);
    setPos(scale*MARGIN , y);
    y += this->boundingRect().height() + 4*scale;
    for(int i = 0 ; i < infos.size() ; i++){
        infos[i]->setParentItem(this);
        infos[i]->setPos(scale * infos[i]->getPos());
    }
}

void Header::save(QTextStream &out, QString Can){
    out << "$";
	for(int i = 0 ; i < infos.size() ; i++)
		infos[i]->save(out);
	out << endl;
}

void Header::mousePressEvent(QGraphicsSceneMouseEvent *event){
    this->setFocus();
    bool selection = false;
    if(selectedElem >=0 && selectedElem < infos.size()){
        infos.at(selectedElem)->setSelected(false);
    }
    for(int i = 0 ; i < infos.size() ; i++)
        if(infos.at(i)->sceneBoundingRect().contains(event->scenePos()) ){
            selectedElem = i;
            infos[i]->setSelected(true);
            selection = true;
        }
    if(!selection)
        selectedElem = -1;
    ElemFocusable::mousePressEvent(event);
}

void Header::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete)
        supr();
    ElemFocusable::keyPressEvent(event);
}

void Header::supr(){
    if(selectedElem != -1 && selectedElem < infos.size()){
        ElemHeader* h = infos.at(selectedElem);
        delete h;
        infos.removeAt(selectedElem);
        selectedElem = -1;
    }
}

void Header::setFont(QFont font , int mode){
    if(selectedElem != -1 && selectedElem < infos.size()){
        infos.at(selectedElem)->setFont(font , mode);
    }
}

void Header::setScale(float scale){
    this->setRect(0,0,(A4_X-2*MARGIN)*scale , 3*LINE_HEIGHT*scale );
    for(int i = 0 ; i < infos.size() ; i++){
        infos[i]->setScale(scale);
    }
}
