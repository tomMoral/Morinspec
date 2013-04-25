#ifndef PHOTO_H
#define PHOTO_H
#include "elemfocusable.h"
#include <QPainter>
#include <QPrinter>
#include <QGraphicsPixmapItem>

class Photo : public ElemFocusable
{
public:
	Photo(QString _photoFile);
    void print(QPainter *painter , int &y , QPrinter &printer);
    virtual void save(QTextStream &out, QString Can);
    void setScale(float scale);

protected:

    void focusInEvent( QFocusEvent *event);
    void focusOutEvent( QFocusEvent *event);
private:
	QString photoFile;
	QGraphicsPixmapItem *photo;
};

#endif // PHOTO_H
