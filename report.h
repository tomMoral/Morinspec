#ifndef REPORT_H
#define REPORT_H
#include "mesures.h"
#include "infoheader.h"
#include "lignemesure.h"
#include "header.h"
#include "elemlist.h"
#include "sautpage.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMessageBox>

class Report
{
public:
    Report(QString filePath , QString _logo = "logo.jpg");
	void print(ElemList *list , QGraphicsScene* scene);
    Mesures* at(int i){ return mesureList[i];}
    int size(){ return mesureList.size();}
    int sizeIH(){ return info.size();}
	InfoHeader atIH(int i){ return info[i];}

private:
    QList<Mesures*> mesureList;
    QList<InfoHeader> info;
    QList<int> partList;
    QString logo;
};

#endif // REPORT_H
