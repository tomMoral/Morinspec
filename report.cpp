#include "report.h"
#include "logoelem.h"
#include "infoheadelem.h"
#include "dimensions.h"
#include "formfit.h"
#include "localisation.h"

Report::Report(QString filePath , QString _logo)
{
    logo = _logo;
    partList <<0;
    QFile reportTxt(filePath);
    if(!reportTxt.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::information(0,"Error","File not found");
    }
    QTextStream in(&reportTxt);
    while(!in.atEnd()){
        QString line = in.readLine();
        if(line[0] != ':'){

            QStringList labels = line.split('\"' , QString::SkipEmptyParts);
            if(labels.size()%2 != 0){
                if(line[0] == '"')
                    info.append(InfoHeader(line));
            }
            else{
                for(int i = 0 ; i < labels.size()/2 ; i++){
                    QString label = labels[2*i];
                    QString val = labels[2*i+1];
                    val = val.remove(val.size()-1,1);
                    val = val.remove(QRegExp("^[\\s+,]"));
                    QStringList fields = val.split(QRegExp("[\\s,]") );
                    if(fields.size() == 5 || fields.size() ==6)
                        mesureList.append(new Dimensions(label , fields[0] , fields[1] , fields[2] , fields[3] , fields[4] ));
                    else if(fields.size() == 1){
                        if(fields.front() != "")
                            mesureList.append(new Dimensions(label , fields[0] ));
                        else
                            info.append(InfoHeader(label + fields[0]));
                    }
                    else if(fields.size() == 2)
                        mesureList.append(new Localisation(label , fields[0] , fields[1] ));
                    else if(fields.size() == 3)
                        mesureList.append(new Localisation(label , fields[0] , fields[1]  , fields[2] ));
                    else if(fields.size() == 7 || fields.size() == 8)
                        mesureList << new Localisation(label , fields[0] , fields[1], fields[2]  ,fields[3] , fields[4] , fields[5] , fields[6]);
                    else{
                        qDebug() << "Non parser : " << fields.size() << "->" << val;
                    }
                }

            }
        }
        else if ( line == ":END")
            partList << mesureList.size() << info.size();
    }
    reportTxt.close();
}

void Report::print(ElemList *list , QGraphicsScene* scene){
    Header *head = new Header("Head");
	list->add(head);
    float currentX = 2;
    float currentY = 2;
    int count = 0 , countPart = 1;
    head->add(new LogoElem(currentX,currentY , logo));
    for(int i = 0 ; i < ((partList.size()<3)?info.size():partList[2]) ; i++)
        head->add(new InfoHeadElem(currentX , currentY , info[i].display() , i, QFont()));
    QStringList entries = QDir("Snapshots").entryList(QDir::Files);
    if(entries.size()>0)
            list->add(new Photo(QString("Snapshots/") + entries[0]));
    QStringList encart;
    encart << "Caractéristique" << "Mesure" << "Nominal" << "Tol+" << "Tol-"<< "Dév/Hors Tol" ;
    list->add(new LigneText(encart,"E",true));
	for(int i = 0 ; i < mesureList.size() ; i ++){
        if(count == partList.at(countPart)){
            countPart+=2;
            if(count != 0){
                list->add(new SautPage());
                head = new Header("Head");
                list->add(head);
                currentX = 2;
                currentY = 2;
                head->add(new LogoElem(currentX,currentY , logo));
                for(int i = partList.at(countPart -1) ; i < partList.at(countPart +1) ; i++)
                    head->add(new InfoHeadElem(currentX , currentY , info[i].display() , i, QFont()));
            }
            list->add(new LigneText(encart,"E",true));
        }
		list->add(new LigneMesure(mesureList[i] , QString("M") + QString::number(i)));
        count++;
    }
	list->print(scene);
}
