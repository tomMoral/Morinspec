#ifndef INFOHEADELEM_H
#define INFOHEADELEM_H
#include "elemheader.h"

class InfoHeadElem : public ElemHeader
{
	int compt;
public:
    InfoHeadElem(float &_x, float &_y,  QString _info , int _compt , QFont font);
	virtual void save(QTextStream &out);
};

#endif // INFOHEADELEM_H
