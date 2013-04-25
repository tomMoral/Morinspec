#include "infoheader.h"

InfoHeader::InfoHeader(QString ligne)
{
    this->name = ligne;
	QStringList fields = ligne.split(',');
    if(fields.size() >4){
		info = fields[1];
		donnees = fields[3];
	}
    else if (fields.size() ==1)
        info = fields[0];
	else{
		info = fields[0];
		donnees = fields[1];

    }
}


QString InfoHeader::display()
{
    if(donnees != "")
        return info + ":" + donnees;
    return info;
}
