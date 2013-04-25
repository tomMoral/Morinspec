#ifndef ELEMFOCUSABLE_H
#define ELEMFOCUSABLE_H

#include <QGraphicsRectItem>
#include <QTextStream>
#include <QDir>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QPrinter>

#define MARGIN 25.
#define SCALE 3.
#define LINE_HEIGHT 8.
#define A4_X 210.
#define A4_Y 297.

class ElemHeader;

class ElemFocusable : public QObject, public QGraphicsRectItem
{
Q_OBJECT
public:
    explicit ElemFocusable(QString _name = "d", bool _Header = false, bool _Encart=false);
	void addChild(QGraphicsItem *rpz);
	QString GetName(){ return name;}
    bool isHeader(){ return Header;}
    bool isEncart(){ return Encart;}
	void SetName(QString _name){name=_name;}
    virtual void setFont(QFont font , int mode=0){}
    virtual void setBold(bool _bold){}
    virtual void print(QGraphicsRectItem *page , int &y, float scale = 3);
    virtual void print(QPainter *painter , int &y  , QPrinter &printer) = 0;
    virtual void save(QTextStream &out, QString Can);
    virtual void add( ElemHeader* elem ){}
    virtual void setScale(float scale);
    virtual bool jump(){ return false;}
    void setPosition(int _position);
    static int currentPage;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void focusInEvent( QFocusEvent *event);
	void focusOutEvent( QFocusEvent *event);

signals:
    void selectedItem(int position);

public slots:

private:
	QString name;
    bool Header;
    int position;

protected:
    bool Encart;

};

#endif // ELEMFOCUSABLE_H
