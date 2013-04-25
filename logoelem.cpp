#include "logoelem.h"

LogoElem::LogoElem(float &_x, float _y, QString _fileName):
    ElemHeader(_x,_y, _fileName , true)
{ fileName = _fileName; }

void LogoElem::save(QTextStream &out){
    out << "E" << getx() << "/" << gety() << ":" << fileName << ";";
}
