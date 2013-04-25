#include "elemlist.h"
#include <QApplication>
#include <QGraphicsScene>
#include "header.h"

int ElemList::selectedElem = 1;
float ElemList::scale = 3;
bool ElemList::bold = false;
QList<QGraphicsRectItem*> ElemList::pages;
QFont ElemList::font = QApplication::font();
ElemList* ElemList::front = NULL;

ElemList::ElemList(int _position): QObject(0)
{
    next = NULL;
	representation = NULL;
	isEmpty = true;
	position = _position;
    if(front == NULL)
        front = this;

}

ElemList::ElemList(ElemList &elem) : QObject(0)
{
	if(elem.isEmpty){
		next = NULL;
		representation = NULL;
		isEmpty = true;
		position = elem.position;
	}
	else {
		next = elem.next;
		representation = elem.representation;
        connect(representation , SIGNAL(selectedItem(int)) , this , SLOT(SelectedItem(int)));
		isEmpty = elem.isEmpty;
		position = elem.position;
	}
}

ElemList::~ElemList(){
		delete next;
}

void ElemList::updatePosition(int p){
    position = p;
    if(!isEmpty)
        representation->setPosition(position);
    if(next != NULL)
        next->updatePosition(p+1);
}

void ElemList::addFront(ElemFocusable *_representation){
    if(isEmpty)
        this->add(_representation);
    else{
        ElemList* tail = new ElemList(*next);
        ElemFocusable* rpz = representation;
        representation = _representation;
        connect(representation , SIGNAL(selectedItem(int)) , this , SLOT(SelectedItem(int)));
        next->representation = rpz;
        next->next = tail;
        next->isEmpty = false;
        representation->setFont(ElemList::font);
        representation->setScale(scale);
        representation->setBold(bold);
        representation->setPosition(position);
        next->updatePosition(position+1);
    }
}

void ElemList::add(ElemFocusable *_representation){
	if(isEmpty){
		representation = _representation;
        connect(representation , SIGNAL(selectedItem(int)) , this , SLOT(SelectedItem(int)));
		isEmpty = false;
		next = new ElemList(position + 1);
        representation->setFont(ElemList::font);
        representation->setBold(bold);
        representation->setPosition(position);
	}
	else
		next->add(_representation);

}

void ElemList::add(ElemHeader* elem){
    if(isEmpty){
        int r = QMessageBox::warning(0,"Error","Il n'y a pas d'entête.\n Voulez vous en ajouter?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(r==QMessageBox::Yes){
            Header* head = new Header();
            front->add(head);
            head->add(elem);
        }
        return;
   }
    if(representation->isHeader())
        representation->add(elem);
    else
        next->add(elem);
}

void ElemList::insert(int i , ElemFocusable *_representation){
    if(isEmpty){
        this->add(_representation);
    }
    else if(i>0)
        next->insert(i-1 , _representation);
    else{
        this->addFront(_representation);
    }
}

void ElemList::insert(ElemFocusable *_representation){
    this->insert(ElemList::selectedElem , _representation);
    ElemList::selectedElem++;
}

ElemFocusable* ElemList::remove(){
    int rm = selectedElem;
    if(selectedElem > 1)
        selectedElem--;
    return this->remove(rm);
}

ElemFocusable* ElemList::remove(int i){
	if(isEmpty) return NULL;
	if(i>0)
		return next->remove(i-1);
	if(next->isEmpty){
		isEmpty = true;
		delete next;
		next = NULL;
		return representation;
	}
	ElemFocusable *rpz = representation;
	representation = next->representation;
    representation->setPosition(position);
    next = next->next;
    next->updatePosition(position+1);
	return rpz;
}

void ElemList::setFont(QFont _font ,int mode , bool global){
    if(!global){
        if(representation->isHeader())
            representation->setFont(_font,  mode);
        else if(next != NULL)
            next->setFont(_font , mode , global);
    }
    else{

        if(!isEmpty && !representation->isHeader())
            representation->setFont(_font,mode);

        if(next != NULL && !next->isEmpty)
            next->setFont(_font,mode,global);
        else{
            if(mode != 0){
                int ps = font.pointSize();
                if(mode > 1){
                    ps-= mode*2-5;
                    _font = font.family();
                }
                _font.setPointSize(ps);
            }
            ElemList::font = _font;
        }
    }
}

void ElemList::setBold(bool _bold){
    if(isEmpty)
        bold = _bold;
    else if(representation->isEncart())
        representation->setBold(_bold);

    if(next != NULL)
        next->setBold(_bold);
}

void ElemList::setScale(float _width ){
    if(_width >0)
        scale = (_width -50)/A4_X;
    if(!isEmpty)
        representation->setScale(scale);
    if(next != NULL)
        next->setScale();
}

void ElemList::print(QGraphicsScene *scene){
	if(!isEmpty){
		for(int i = 0 ; i < pages.size() ; i++){
			QList<QGraphicsItem* > childs = pages[i]->childItems();
			for(int j = 0 ; j < childs.size() ; j++)
				childs[j]->setParentItem(0);
			delete pages[i];
		}
		pages.clear();
        int y = 0;
		QGraphicsRectItem *page = newPage(scene , y );
		this->print(scene , page,y );
	}
}

void ElemList::print(QGraphicsScene *scene ,QGraphicsRectItem *page , int &y ){
	if(isEmpty) return;
    float h = representation->boundingRect().height();
    float basP = page->boundingRect().y() + page->boundingRect().height();
    if( basP - (y + h)  < MARGIN*scale || representation->jump())
		page = newPage(scene , y);
    representation->print(page , y,scale);
    next->print(scene , page, y);
}

void ElemList::print(bool pdf){
    QPrinter pdfPrinter;
    pdfPrinter.setResolution(500);
    QString saveName = "Document";
    if(pdf){
        pdfPrinter.setOutputFormat(QPrinter::PdfFormat);
        QString saveName = QFileDialog::getSaveFileName(0,"Save name",QString() , "*.pdf");
        pdfPrinter.setOutputFileName(saveName);
    }
	pdfPrinter.setOrientation(QPrinter::Portrait);
	pdfPrinter.setPaperSize(QPrinter::A4);
    pdfPrinter.setFullPage(true);

	QPainter painter;
    if(!painter.begin(&pdfPrinter)){
        QMessageBox::warning(0,"Impression" , QString("Echec de l'impression de ") + saveName.split("/").back() );
        return;
    }
    painter.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing|QPainter::SmoothPixmapTransform);
    float scaleP = pdfPrinter.paperRect().width()/A4_X;

    ElemFocusable::currentPage = 1;
    painter.setFont(QFont("Arial" , 9));
    painter.drawText((A4_X-8)*scaleP , (A4_Y-6)*scaleP , QString::number(ElemFocusable::currentPage));
    painter.setFont(QFont("Arial" , 6));
    painter.drawText((3*MARGIN)*scaleP , (A4_Y-6)*scaleP , "Rapport realisé sur une machine MicroVu");
    painter.setFont(QFont("Arial" , 9));
    int y = MARGIN * scaleP;
	print(&painter , y , pdfPrinter);
	painter.end();
    QMessageBox::information(0,"Impression" , QString("Fin de l'impression de ") + saveName.split("/").back() );
}

void ElemList::print(QPainter *painter , int &y , QPrinter &printer){
	if(isEmpty) return;
	representation->print(painter , y , printer);
	next->print(painter , y , printer);
}


QString ElemList::save(){
    QDir Can("Canvas");
    bool ok = false , can = true;
    QString canvaName;
    while(!ok){
        canvaName = QInputDialog::getText(0,"Sauvegarde du modèle" , "Nom du Modèle",QLineEdit::Normal , " " , &can );
        if(!can) return "";
        ok = true;
        if(Can.entryList(QDir::AllDirs).contains(canvaName)){
            int i = QMessageBox::warning(0,"Alert" , QString("Voulez vous écraser le modèle ") + canvaName.split('/').back() + "?" ,
                                 QMessageBox::Save|QMessageBox::Cancel,QMessageBox::Cancel);
            ok = (i==QMessageBox::Save);
        }
    }

    Can.mkdir(canvaName);
    Can.cd(canvaName);
    Can.remove(Can.path()+"/"+canvaName.split("/").back()+".can");
    QFile outFile(Can.path()+"/"+canvaName.split("/").back()+".can");
	if(!outFile.open(QIODevice::Truncate|QIODevice::WriteOnly|QIODevice::Text))
	{
		qDebug()<< "Issue";
        return "";
	}
    QTextStream out( &outFile );
    out << "F:" << font.pointSize() << ":" << font.family() << ":" << ((bold)?"B":"b") << ":" << endl;
    save(out ,Can.path());
    return canvaName;
}

void ElemList::save(QTextStream &out , QString Can){
	if(isEmpty) return;
    representation->save(out , Can);
    next->save(out , Can);
}

void ElemList::SelectedItem(int pos){
    selectedElem = pos;
}

void ElemList::clear(){
	while(!isEmpty)
		delete remove(0);
    bold = false;
    font = QFont("Arial" , 8);
}
int ElemList::size(){
    if(isEmpty)
        return 0;
    return next->size()+1;
}

QGraphicsRectItem* ElemList::newPage(QGraphicsScene *scene , int &y){
    if(y == (pages.size()-1)*(A4_Y+10 +MARGIN)*scale)
        return pages.back();
    int n = pages.size();
    y = n*(A4_Y+10)*scale;
    QGraphicsRectItem* page = new QGraphicsRectItem(20, y , A4_X*scale , A4_Y*scale, 0 , scene);
    pages.push_back(page);
    y+= scale * MARGIN;
    page->setBrush(QBrush(Qt::white));
    return page;
}
