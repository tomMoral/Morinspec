#ifndef LIGNECOM_H
#define LIGNECOM_H
#include "ligne.h"

class LigneCom : public Ligne
{
private:
    QGraphicsTextItem *info;
    QString infoText ;
    QFont font;
    float scale;
public:
    LigneCom(QString _info );
    ~LigneCom();
    void print(QPainter *painter , int &y , QPrinter &printer);
    void setScale(float scale);
    void setFont(QFont _font, int mode);

};

#endif // LIGNECOM_H
