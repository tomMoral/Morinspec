#include "lignemesure.h"
#include <math.h>
#include <QPainter>
#include <QDebug>

LigneMesure::LigneMesure(Mesures *mesure ,QString name) : LigneText(mesure->textList(), name)
{

    if(mesure->isToleranced()){

        boxLength = 14;
        int margeX = 2;
        float boxHeight = 4.;
        int x = (160-boxLength-2*margeX-1)*SCALE;
        int y0 = (LINE_HEIGHT*this->getLh()- boxHeight)*SCALE/2;

        box = new QGraphicsRectItem(x+margeX*SCALE , y0 , boxLength*SCALE,boxHeight*SCALE,this);
        box->setZValue(3);
        ecart = mesure->getEcart();
        tolP = mesure->getToleranceSup(), tolM = mesure->getToleranceInf();
        center = (tolP*tolM<0);
        if(ecart >0 && tolP>0)
            length = ecart/tolP;
        else if(ecart <0 && tolM <0)
            length = -ecart/tolM;
        else{
            center = true;
            if(ecart >0)
                length =  1;
            else
                length = -1;
        }
        if(fabs(length)>1)
            length /= fabs(length);
        if(center){
            length /= 2;
            boxVal = new QGraphicsRectItem(x+(boxLength/2+margeX)*SCALE , y0 , length*boxLength*SCALE,boxHeight*SCALE,this);
            boxVal->setZValue(-1);
            boxVal->setPen(QPen(Qt::NoPen));
            barres << new QGraphicsLineItem(x+(boxLength/2+margeX)*SCALE,y0,x+(boxLength/2+margeX)*SCALE , y0+boxHeight*SCALE, this);
            barres << new QGraphicsLineItem(x+(boxLength/4+margeX)*SCALE,y0+boxHeight*SCALE/2,x+(boxLength/4+margeX)*SCALE , y0+boxHeight*SCALE, this);
            barres << new QGraphicsLineItem(x+(3*boxLength/4+margeX)*SCALE,y0+boxHeight*SCALE/2,x+(3*boxLength/4+margeX)*SCALE , y0+boxHeight*SCALE, this);
            barres << new QGraphicsLineItem(x+(boxLength/8+margeX)*SCALE,y0+3*boxHeight*SCALE/4,x+(boxLength/8+margeX)*SCALE , y0+boxHeight*SCALE, this);
            barres << new QGraphicsLineItem(x+(3*boxLength/8+margeX)*SCALE,y0+3*boxHeight*SCALE/4,x+(3*boxLength/8+margeX)*SCALE , y0+boxHeight*SCALE, this);
            barres << new QGraphicsLineItem(x+(5*boxLength/8+margeX)*SCALE,y0+3*boxHeight*SCALE/4,x+(5*boxLength/8+margeX)*SCALE , y0+boxHeight*SCALE, this);
            barres << new QGraphicsLineItem(x+(7*boxLength/8+margeX)*SCALE,y0+3*boxHeight*SCALE/4,x+(7*boxLength/8+margeX)*SCALE , y0+boxHeight*SCALE, this);
            barres << new QGraphicsLineItem(x+0*SCALE,y0+(boxHeight/2)*SCALE,x+(margeX-.5)*SCALE , y0+(boxHeight/2)*SCALE, this);
            barres << new QGraphicsLineItem(x+(margeX+boxLength +.5)*SCALE,y0+(boxHeight/2)*SCALE,x+(2*margeX+boxLength)*SCALE, y0+(boxHeight/2)*SCALE, this);
            barres << new QGraphicsLineItem(x+(margeX+boxLength +.5+(margeX-.5)/2)*SCALE,y0+boxHeight/4.*SCALE,x+(margeX+boxLength +.5+(margeX-.5)/2)*SCALE , y0+3*boxHeight/4.*SCALE, this);

            if(tolM*0.7 < ecart && ecart < 0.7*tolP)
                boxVal->setBrush(QBrush(Qt::green));
            else if (tolM < ecart && ecart < tolP)
                boxVal->setBrush(QBrush(QColor(255,130,19)));
            else
                boxVal->setBrush(QBrush(Qt::red));
        }
        else{
            if(length > 0)
                boxVal = new QGraphicsRectItem(x+margeX*SCALE , y0 , length*boxLength*SCALE,boxHeight*SCALE,this);
            else{
                boxVal = new QGraphicsRectItem(x+(margeX+boxLength)*SCALE , y0 , length*boxLength*SCALE,boxHeight*SCALE,this);
            }
            boxVal->setZValue(-1);
            boxVal->setPen(QPen(Qt::NoPen));
            barres << new QGraphicsLineItem(x+(boxLength/2+margeX)*SCALE,y0+boxHeight*SCALE/2,x+(boxLength/2+margeX)*SCALE , y0+boxHeight*SCALE, this);
            barres << new QGraphicsLineItem(x+(boxLength/4+margeX)*SCALE,y0+3*boxHeight*SCALE/4,x+(boxLength/4+margeX)*SCALE , y0+boxHeight*SCALE, this);
            barres << new QGraphicsLineItem(x+(3*boxLength/4+margeX)*SCALE,y0+3*boxHeight*SCALE/4,x+(3*boxLength/4+margeX)*SCALE , y0+boxHeight*SCALE, this);

            if(tolM*0.7 < ecart && ecart < 0.7*tolP)
                boxVal->setBrush(QBrush(Qt::green));
            else if (tolM < ecart && ecart < tolP)
                boxVal->setBrush(QBrush(QColor(255,130,19)));
            else
                boxVal->setBrush(QBrush(Qt::red));
        }
    }
	else{
		boxVal = NULL;
		box = NULL;
	}
}

LigneMesure::~LigneMesure(){
	delete this->boxVal;
	delete this->box;
}

void LigneMesure::print(QPainter *painter , int &y , QPrinter &printer){


    float scaleP = printer.paperRect().width()/A4_X;
    int margeX = 2;
    int margeY = 2;
    int boxHeight = LINE_HEIGHT - 2*margeY;
    int x0 = (A4_X-MARGIN-2*margeX - boxLength -1)*scaleP;
    int y0 = y+(LINE_HEIGHT*this->getLh()- boxHeight)*scaleP/2;

    LigneText::print(painter,y,printer);


    if (y0 > y)
        y0 = MARGIN*scaleP+(LINE_HEIGHT*this->getLh()- boxHeight)*scaleP/2;

	if(box != NULL){

        if(center){
            float moy = (tolP+tolM)/2.;
            if((tolM-moy)*0.7 < ecart-moy && ecart-moy < 0.7*(tolP-moy))
                painter->setBrush(QBrush(Qt::green));
            else if (tolM < ecart && ecart < tolP)
                painter->setBrush(QBrush(QColor(255,130,19)));
            else
                painter->setBrush(QBrush(Qt::red));
            if(isnan(length))
                length = 0;
            painter->setPen(Qt::NoPen);
            painter->drawRect(x0+(margeX+boxLength/2)*scaleP , y0 , length*boxLength*scaleP,boxHeight*scaleP);

            painter->setPen(QPen(Qt::SolidLine));
            painter->setBrush(QBrush(Qt::NoBrush));
            painter->drawRect(x0+margeX*scaleP , y0 , boxLength*scaleP,boxHeight*scaleP);
            painter->drawLine(x0+(margeX+boxLength/2)*scaleP,y0   ,x0+(margeX+boxLength/2)*scaleP , y0+boxHeight*scaleP);
            painter->drawLine(x0+(margeX+boxLength/4)*scaleP,y0+boxHeight*scaleP/2 ,x0+(margeX+boxLength/4)*scaleP , y0+boxHeight*scaleP);
            painter->drawLine(x0+(margeX+3*boxLength/4)*scaleP,y0+boxHeight*scaleP/2 ,x0+(margeX+3*boxLength/4)*scaleP , y0+boxHeight*scaleP);
            painter->drawLine(x0+(margeX+boxLength/8)*scaleP,y0+3*boxHeight*scaleP/4 ,x0+(margeX+boxLength/8)*scaleP , y0+boxHeight*scaleP);
            painter->drawLine(x0+(margeX+3*boxLength/8)*scaleP,y0+3*boxHeight*scaleP/4 ,x0+(margeX+3*boxLength/8)*scaleP , y0+boxHeight*scaleP);
            painter->drawLine(x0+(margeX+5*boxLength/8)*scaleP,y0+3*boxHeight*scaleP/4 ,x0+(margeX+5*boxLength/8)*scaleP , y0+boxHeight*scaleP);
            painter->drawLine(x0+(margeX+7*boxLength/8)*scaleP,y0+3*boxHeight*scaleP/4 ,x0+(margeX+7*boxLength/8)*scaleP , y0+boxHeight*scaleP);
            painter->drawLine(x0+0*scaleP ,y0+boxHeight*scaleP/2,x0+(margeX-0.5)*scaleP  , y0+boxHeight*scaleP/2);
            painter->drawLine(x0+(margeX+boxLength+0.5)*scaleP,y0+boxHeight*scaleP/2,x0+(2*margeX+boxLength)*scaleP , y0+boxHeight*scaleP/2);
            painter->drawLine(x0+(margeX+boxLength+0.5+(margeX-0.5)/2)*scaleP ,y0+boxHeight/4*scaleP ,x0+(margeX+boxLength+0.5+(margeX-0.5)/2)*scaleP  , y0+3*boxHeight/4*scaleP);
        }
        else{
            if(tolM*0.7 < ecart && ecart < 0.7*tolP)
                painter->setBrush(QBrush(Qt::green));
            else if (tolM < ecart && ecart < tolP)
                painter->setBrush(QBrush(QColor(255,130,19)));
            else
                painter->setBrush(QBrush(Qt::red));
            painter->setPen(Qt::NoPen);
            if(length > 0)
               painter->drawRect(x0+(margeX)*scaleP , y0 , length*boxLength*scaleP,boxHeight*scaleP);
            else{
                painter->drawRect(x0+(margeX+boxLength)*scaleP , y0 , length*boxLength*scaleP,boxHeight*scaleP);
            }

            painter->setPen(QPen(Qt::SolidLine));
            painter->setBrush(QBrush(Qt::NoBrush));
            painter->drawRect(x0+margeX*scaleP , y0 , boxLength*scaleP,boxHeight*scaleP);
            painter->drawLine(x0+(margeX+boxLength/2)*scaleP,y0+boxHeight*scaleP/2 ,x0+(margeX+boxLength/2)*scaleP , y0+boxHeight*scaleP);
            painter->drawLine(x0+(margeX+boxLength/4)*scaleP,y0+3*boxHeight*scaleP/4 ,x0+(margeX+boxLength/4)*scaleP , y0+boxHeight*scaleP);
            painter->drawLine(x0+(margeX+3*boxLength/4)*scaleP,y0+3*boxHeight*scaleP/4 ,x0+(margeX+3*boxLength/4)*scaleP , y0+boxHeight*scaleP);
        }
    }
}

void LigneMesure::setScale(float scale){
    LigneText::setScale(scale);
    if(box != NULL){
        for(int i = 0 ; i < barres.size() ; i++)
            delete barres[i];
        int margeX = 2;
        float boxHeight = 4.;
        int x = (160-boxLength-2*margeX-1)*scale;
        int y0 = (LINE_HEIGHT*this->getLh()- boxHeight)*scale/2;

        box->setRect(x+margeX*scale , y0 , boxLength*scale,boxHeight*scale);
        if(center){
            boxVal->setRect(x+(boxLength/2+margeX)*scale , y0 , length*boxLength*scale,boxHeight*scale);
            barres.clear();
            barres << new QGraphicsLineItem(x+(boxLength/2+margeX)*scale,y0,x+(boxLength/2+margeX)*scale , y0+boxHeight*scale, this);
            barres << new QGraphicsLineItem(x+(boxLength/4+margeX)*scale,y0+boxHeight*scale/2,x+(boxLength/4+margeX)*scale , y0+boxHeight*scale, this);
            barres << new QGraphicsLineItem(x+(3*boxLength/4+margeX)*scale,y0+boxHeight*scale/2,x+(3*boxLength/4+margeX)*scale , y0+boxHeight*scale, this);
            barres << new QGraphicsLineItem(x+(boxLength/8+margeX)*scale,y0+3*boxHeight*scale/4,x+(boxLength/8+margeX)*scale , y0+boxHeight*scale, this);
            barres << new QGraphicsLineItem(x+(3*boxLength/8+margeX)*scale,y0+3*boxHeight*scale/4,x+(3*boxLength/8+margeX)*scale , y0+boxHeight*scale, this);
            barres << new QGraphicsLineItem(x+(5*boxLength/8+margeX)*scale,y0+3*boxHeight*scale/4,x+(5*boxLength/8+margeX)*scale , y0+boxHeight*scale, this);
            barres << new QGraphicsLineItem(x+(7*boxLength/8+margeX)*scale,y0+3*boxHeight*scale/4,x+(7*boxLength/8+margeX)*scale , y0+boxHeight*scale, this);
            barres << new QGraphicsLineItem(x+0*scale,y0+(boxHeight/2)*scale,x+(margeX-.5)*scale , y0+(boxHeight/2)*scale, this);
            barres << new QGraphicsLineItem(x+(margeX+boxLength +.5)*scale,y0+(boxHeight/2)*scale,x+(2*margeX+boxLength)*scale, y0+(boxHeight/2)*scale, this);
            barres << new QGraphicsLineItem(x+(margeX+boxLength +.5+(margeX-.5)/2)*scale,y0+boxHeight/4.*scale,x+(margeX+boxLength +.5+(margeX-.5)/2)*scale , y0+3*boxHeight/4.*scale, this);
        }
        else{
            if(length > 0)
                boxVal->setRect(x+margeX*scale , y0 , length*boxLength*scale,boxHeight*scale);
            else{
                boxVal->setRect(x+(margeX+boxLength)*scale , y0 , length*boxLength*scale,boxHeight*scale);
            }
            barres.clear();
            barres << new QGraphicsLineItem(x+(boxLength/2+margeX)*scale,y0+boxHeight*scale/2,x+(boxLength/2+margeX)*scale , y0+boxHeight*scale, this);
            barres << new QGraphicsLineItem(x+(boxLength/4+margeX)*scale,y0+3*boxHeight*scale/4,x+(boxLength/4+margeX)*scale , y0+boxHeight*scale, this);
            barres << new QGraphicsLineItem(x+(3*boxLength/4+margeX)*scale,y0+3*boxHeight*scale/4,x+(3*boxLength/4+margeX)*scale , y0+boxHeight*scale, this);
        }
    }
}
