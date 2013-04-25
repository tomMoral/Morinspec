#include "infoheadelem.h"

InfoHeadElem::InfoHeadElem(float &_x, float &_y, QString _info , int _compt, QFont font) : ElemHeader(_x,_y, _info.remove("\""))
{
	compt = _compt;
    this->setFont(font);
}

void InfoHeadElem::save(QTextStream &out){
    QFont font = getFont();
    out << "E" << getx() << "/" << gety() << ":F," << font.pointSize() << "," << font.family() << ":"<< "I" << compt << ";";
}
