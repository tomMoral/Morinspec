#include "nameelem.h"
#include <QInputDialog>

float NameElem::wasteX = (A4_X - 2 * MARGIN);
float NameElem::wasteY = LINE_HEIGHT*2;

NameElem::NameElem() :
    ElemHeader(wasteX, wasteY , QString("Nom : ") + QInputDialog::getText(0,"Name" , "Give your name :"))
{
    wasteX = (A4_X - 2 * MARGIN);
    wasteY = LINE_HEIGHT*2;
    this->setx(this->getx()-this->boundingRect().width()/SCALE-1);
}

NameElem::NameElem(float &_x , float &_y, QFont font ) :
    ElemHeader(_x,_y, QString("Nom : ") +QInputDialog::getText(0,"Name" , "Give your name :"))
{
    this->setFont(font);
}

void NameElem::save(QTextStream &out){
    QFont font = getFont();
    out << "E" << getx() << "/" << gety() << ":F," << font.pointSize() << ","  << font.family() <<":N" << ";";
}

