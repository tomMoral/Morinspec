#ifndef NAMEELEM_H
#define NAMEELEM_H
#include "elemheader.h"

class NameElem : public ElemHeader
{
public:
    NameElem();
    NameElem(float &_x, float &_y , QFont font);
	virtual void save(QTextStream &out);
    static float wasteX , wasteY;
};

#endif // NAMEELEM_H
