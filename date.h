#ifndef DATE_H
#define DATE_H
#include "elemheader.h"
#include <QDateTime>

class Date : public ElemHeader
{
public:
    Date();
    Date(float &_x, float &_y , QFont font);
    virtual void save(QTextStream &out);
    static float wasteX , wasteY;
};

#endif // DATE_H
