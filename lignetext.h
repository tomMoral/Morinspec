#ifndef LIGNETEXT_H
#define LIGNETEXT_H
#include "ligne.h"
#include <QApplication>

class LigneText : public Ligne
{
private:
    QList<QGraphicsTextItem *> representations;
    QList<QGraphicsRectItem *> shades;
    QStringList Texts;
    QFont font;
    float scale;
public:
    LigneText(QStringList encart , QString _name = "E", bool _title = false);
	~LigneText();
    void print(QPainter *painter , int &y , QPrinter &printer);
    void setFont(QFont _font, int mode = 0);
    void setBold(bool _bold);
    void shading();

    virtual void setScale(float _scale);
};

#endif // LIGNETEXT_H
