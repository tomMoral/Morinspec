#include "commentelem.h"

float CommentElem::wasteX = 0;
float CommentElem::wasteY = 0;

CommentElem::CommentElem(QString _info,float _scale):
    ElemHeader(wasteX,wasteY ,_info )
{
    wasteX = 0 , wasteY = 0;
    info = _info;
    this->setx(((A4_X - 2 * MARGIN)-this->boundingRect().width()/_scale)/2);
    this->sety(((LINE_HEIGHT*3)-this->boundingRect().height()/_scale)/2);
}

CommentElem::CommentElem(float &_x, float &_y , QString info, QFont font ) :
    ElemHeader(_x,_y , info)
{
    this->setFont(font);
}

void CommentElem::save(QTextStream &out){
    QFont font = getFont();
    out << "E" << getx() << "/" << gety() << ":F," << font.pointSize() << ","  << font.family() <<":@" << info << ";";
}
