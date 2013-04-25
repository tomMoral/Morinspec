#ifndef INFOHEADER_H
#define INFOHEADER_H
#include <QStringList>

class InfoHeader
{
public:
    InfoHeader(QString ligne = "");
	QString display();
private:
	QString name,info , donnees;
};

#endif // INFOHEADER_H
