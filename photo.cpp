#include "photo.h"

Photo::Photo(QString _photoFile):
	ElemFocusable(_photoFile)
{
    photoFile = _photoFile;
    photo = new QGraphicsPixmapItem(QPixmap(_photoFile,photoFile.split('.').back().toStdString().c_str()).scaled((A4_X-2*MARGIN)*SCALE , (A4_Y-2*MARGIN)*SCALE/2 ,Qt::KeepAspectRatio, Qt::SmoothTransformation),this);
    photo->setPos((A4_X-2*MARGIN)*SCALE/2-photo->boundingRect().width()/2+1,1);
    photo->setZValue(-2);
    QGraphicsRectItem::setRect((A4_X-2*MARGIN)*SCALE/2-photo->boundingRect().width()/2,0,photo->boundingRect().width()+1 , photo->boundingRect().height()+1);
}

void Photo::print(QPainter *painter , int &y , QPrinter &printer){
    float scaleP = printer.paperRect().width()/A4_X;
    QPixmap p(GetName(),GetName().split('.').back().toStdString().c_str());
    p = p.scaled((A4_X-2*MARGIN)*scaleP , (A4_Y-2*MARGIN)*scaleP/2 ,Qt::KeepAspectRatio, Qt::SmoothTransformation);

    if(y+p.height() > (A4_Y-MARGIN)*scaleP){
		printer.newPage();
        y = MARGIN * scaleP;
        ElemFocusable::currentPage++;
        painter->drawText((A4_X-8)*scaleP , (A4_Y-6)*scaleP , QString::number(ElemFocusable::currentPage));
        painter->setFont(QFont("Arial" , 6));
        painter->drawText((3*MARGIN)*scaleP , (A4_Y-6)*scaleP , "Rapport realisé sur une machine MicroVu");
        painter->setFont(QFont("Arial" , 8));
	}

    painter->drawPixmap(A4_X*scaleP/2-p.width()/2+1,y,p);
    QPen pen(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->drawRect(A4_X*scaleP/2-p.width()/2 , y , p.rect().width()+2, p.rect().height()+2);
    y += p.rect().height()+2;
}


void Photo::save(QTextStream &out , QString Can){
    QFile photoF(photoFile);
    QString fileName = Can +"/" + photoF.fileName().split('/').back();
    photoF.copy(fileName);
    out << fileName << endl;
}

void Photo::setScale(float scale){
    delete photo;
    photo = new QGraphicsPixmapItem(QPixmap(photoFile,photoFile.split('.').back().toStdString().c_str()).scaled((A4_X-2*MARGIN)*scale , (A4_Y-2*MARGIN)*scale/2 ,Qt::KeepAspectRatio, Qt::SmoothTransformation),this);
    QGraphicsRectItem::setRect((A4_X-2*MARGIN)*scale/2-photo->boundingRect().width()/2,0,photo->boundingRect().width()+1.5 , photo->boundingRect().height()+1);
    photo->setPos((A4_X-2*MARGIN)*scale/2-photo->boundingRect().width()/2+1,1);
}

 void Photo::focusInEvent( QFocusEvent *event){
     this->setPen(QPen(Qt::red));
     ElemFocusable::focusInEvent(event);
 }

 void Photo::focusOutEvent( QFocusEvent *event){
     this->setPen(QPen(Qt::black));
     ElemFocusable::focusOutEvent(event);
 }
