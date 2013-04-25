#ifndef ELEMHEADER_H
#define ELEMHEADER_H
#include "header.h"

#include <QGraphicsRectItem>
#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>


class Header;


class ElemHeader : public QGraphicsRectItem
{
public:
    ElemHeader(float &_x, float &_y , QString _info = "" , bool _logo = false);
    ~ElemHeader();
    virtual void save(QTextStream &out) = 0;
	int getx(){ return x;}
    int gety(){ return y;}
    void setx(float _x){ x = _x; this->setPos(scaleRatio*x,scaleRatio*y);}
    void sety(float _y){ y = _y; this->setPos(scaleRatio*x,scaleRatio*y);}
    QPointF getPos(){ return QPointF(x,y);}
    void print(QPainter* painter , int offsetX =0 ,int offsetY =0, float scaleP = 1.);
    void setFont( QFont _font , int mode = 0);
    void setSelected(bool selected);
    virtual void setScale(float scale);

private:
    float x, y;
    float scaleRatio;
    QString info;
	bool moves , logo;
    QGraphicsTextItem *tex;
    QGraphicsPixmapItem *pix;
    QFont font;

protected:
    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );
	void mousePressEvent ( QGraphicsSceneMouseEvent * event );
	void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    QFont getFont(){ return font;}
};

#endif // ELEMHEADER_H
