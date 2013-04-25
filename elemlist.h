#ifndef ELEMLIST_H
#define ELEMLIST_H

#include "elemfocusable.h"
#include "ligne.h"
#include "photo.h"
#include <QBrush>
#include <QTextStream>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QPrinter>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class ElemList: public QObject
{
Q_OBJECT
public:
	explicit ElemList(int _position = 0);
	explicit ElemList(ElemList &elem);
	~ElemList();
    void updatePosition(int p);
    void addFront(ElemFocusable *_representation);
    void add(ElemFocusable *_representation);
    void add(ElemHeader* elem);
	void insert(int i , ElemFocusable *_representation);
    void insert(ElemFocusable *_representation);
	ElemFocusable* remove(int i);
    ElemFocusable* remove();
    void setFont(QFont _font, int mode = 1, bool global = false);
    void setBold(bool _bold);

    void print(QGraphicsScene *scene , QGraphicsRectItem *page , int &y);
    void print(bool pdf = true);
    virtual void print(QPainter *painter , int &y , QPrinter &printer);
    QString save();
    void save(QTextStream &out, QString Can);
	void clear();
    int size();
    void setScale(float _width = -1);

    //Debug function
    void show();




signals:

public slots:
    void print(QGraphicsScene *scene);
    void SelectedItem(int pos);



private:
    //Static members
	static int selectedElem;
	static QList<QGraphicsRectItem*> pages;
    static float scale;
    static QFont font;
    static bool bold;
    static ElemList* front;

    //Definition de la liste
	ElemList *next;
	ElemFocusable *representation;
	int position;
    bool isEmpty;

    //Invoque une nouvelle page pour le dessin du rapport
    static QGraphicsRectItem* newPage(QGraphicsScene *scene , int &y);


};

//Related function



#endif // ELEMLIST_H
