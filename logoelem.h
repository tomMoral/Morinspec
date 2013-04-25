#ifndef LOGOELEM_H
#define LOGOELEM_H
#include "elemheader.h"

class LogoElem : public ElemHeader
{
public:
    LogoElem(float &_x, float _y, QString _fileName);
    virtual void save(QTextStream &out);

private:
    QString fileName;
    bool rs;
};

#endif // LOGOELEM_H
