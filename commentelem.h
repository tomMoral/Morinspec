#ifndef COMMENTELEM_H
#define COMMENTELEM_H
#include "elemheader.h"
#include <QInputDialog>

class CommentElem : public ElemHeader
{
public:
    CommentElem(QString _info, float _scale = SCALE);
    CommentElem(float &_x, float &_y, QString info , QFont font );
    void save(QTextStream &out);
    static float wasteX , wasteY;

private:
    QString info;
};

#endif // COMMENTELEM_H
