#include "date.h"

float Date::wasteY = 4;
float Date::wasteX = 0;

Date::Date() :
    ElemHeader(wasteX, wasteY , QDateTime::currentDateTime().toString("hh:mm dd/MM/yyyy"))
{
    wasteX = 0 ;
    wasteY = 4;
    this->setx((A4_X - 2 * MARGIN)-this->boundingRect().width()/SCALE-1);
}

Date::Date(float &_x, float &_y, QFont font ) :
    ElemHeader(_x,_y , QDateTime::currentDateTime().toString("hh:mm dd/MM/yyyy"))
{
    this->setFont(font);
}

void Date::save(QTextStream &out){
    QFont font = getFont();
    out << "E" << getx() << "/" << gety() << ":F," << font.pointSize() << ","  << font.family() <<":D" << ";";
}
