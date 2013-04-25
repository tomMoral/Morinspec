#ifndef HEADER_H
#define HEADER_H
#include "elemfocusable.h"
#include "elemheader.h"


class ElemHeader;

class Header : public ElemFocusable
{
public:
	Header(QString _HeaderFile = "");
	void print(QPainter *painter , int &y , QPrinter &printer);
    virtual void print(QGraphicsRectItem *page , int &y , float scale = 3);
    virtual void save(QTextStream &out, QString Can);
	void addInfo(QString info , int i =0);
	void addLogo(QString photoName);
	void add(ElemHeader* elem );
    virtual void setFont(QFont font , int mode);
    virtual void setScale(float scale );

 public slots:
    void supr();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
	QList<ElemHeader*> infos;
    int selectedElem;
};

#endif // HEADER_H
