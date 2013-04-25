#include "reportdialog.h"
#include "ui_reportdialog.h"
#include "lignemesure.h"
#include "lignecom.h"
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>

#include "date.h"
#include "nameelem.h"
#include "logoelem.h"
#include "infoheadelem.h"
#include "commentelem.h"

ReportDialog::ReportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportDialog)
{
    ui->setupUi(this);
    this->scene = new QGraphicsScene();
    this->scene->setBackgroundBrush(Qt::gray);
    ui->reportDisplay->setScene(scene);


	//Load available Canvas
	QDir dirCanva("Canvas");
	QStringList filters;
	filters << "*.can";
	dirCanva.setNameFilters(filters);
    dirCanva.setFilter(QDir::AllDirs);
	QFileInfoList list = dirCanva.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
		 QFileInfo fileInfo = list.at(i);
         if(fileInfo.fileName()[0]!='.'){
             ui->canvasComboBox->addItem(fileInfo.fileName());
         }
	 }
	elemList = new ElemList();
    elemList->setScale(ui->reportDisplay->width());
    elemList->setFont(QFont("Arial" , 8) , 0, true);
	donnees = NULL;
    control = false;
}

ReportDialog::~ReportDialog()
{
    delete ui;
    delete donnees;
    delete elemList;
}

void ReportDialog::on_canvasComboBox_currentIndexChanged(QString text){
    if(text == "Standard"){
        elemList->clear();
        donnees->print(elemList , scene);
        elemList->setScale(ui->reportDisplay->width());
        elemList->print(scene);
        return;
    }
    QFile input(QString("Canvas/") + text + "/"+text + ".can");
    elemList->setFont(QFont("Arial" , 8) , 0, true);
	input.open(QIODevice::ReadOnly);
    elemList->clear();
    ui->boldCheckBox->setCheckState(Qt::Unchecked);
	while(!input.atEnd()){
		QString line = input.readLine();
		line = line.remove(line.size()-2 , 2);
        if(line[0] == 'F'){
            QRegExp rFont("F:(\\d+):([^:]+):([Bb]?)");
            if(rFont.indexIn(line) != -1){
                int ps = rFont.cap(1).toInt();
                QString family = rFont.cap(2);
                elemList->setFont(QFont(family,ps),0,true);
                elemList->setBold((rFont.cap(3)=="B"));
                if(rFont.cap(3)=="B")
                    ui->boldCheckBox->setCheckState(Qt::Checked);
            }

        }
        else if(line == "E"){
			QStringList encart;
            encart << "Caractéristique" << "Mesure" << "Nominal" << "Tol+" << "Tol-"<< "Dév/Hors Tol" ;
            elemList->add(new LigneText(encart , "E" , true));
		}
		else if(line[0] == 'M'){
			int i =1;
			int number = line[i].toAscii()-48;
			int res = 0;
			while(number>-1 && number <10){
				res = res*10+number;
				i++;
				number = line[i].toAscii()-48;
			}
            if(donnees->size() > res)
                elemList->add(new LigneMesure(donnees->at(res) , QString("M") + QString::number(res)));
		}
		else if(line == "New Ligne")
			elemList->add(new Ligne());
        else if(line[0] == '$'){
			Header *head = new Header();
			elemList->add(head);
			int pos = 0;
            QRegExp rx("E(-?\\d+)/(-?\\d+)(:[^;:]*)?:([^;]+)") , rxIH("^I(\\d+)$"), rxF("F,(\\d+),([^:]*)");
            while ((pos = rx.indexIn(line, pos)) != -1) {
				pos += rx.matchedLength();
                QString elem = rx.cap(4);
                QString fontString = rx.cap(3);
                int f = rxF.indexIn(fontString);
                QFont font = QApplication::font();
                if(f != -1){
                    int ps = rxF.cap(1).toInt();
                    QString family = rxF.cap(2);
                    font.setPointSize(ps);
                    font.setFamily(family);
                }
                float x = rx.cap(1).toInt();
                float y = rx.cap(2).toInt();
				if(elem == "D")
                    head->add(new Date(x , y , font));
				else if(elem == "N")
                    head->add(new NameElem(x , y , font));
                else if(rxIH.indexIn(elem)!=-1){
					elem = elem.remove(0,1);
                    int i = elem.toInt();
                    if(i < donnees->sizeIH() && i >=0)
                        head->add(new InfoHeadElem(x , y, donnees->atIH(i).display() , i , font));
				}
                else if(elem.at(0) == '@'){
                    elem = elem.remove(0,1);
                    head->add(new CommentElem(x,y,elem , font));
                }
                else{
                    head->add(new LogoElem(x , y , elem));
                }
            }
		}
        else if(line[0] == '@'){
            line = line.remove(0,1);
            elemList->add(new LigneCom(line));
        }
        else
            elemList->add(new Photo(line));

	}
    elemList->setScale(ui->reportDisplay->width());
	elemList->print(scene);
}

void ReportDialog::on_dateButton_clicked(){
    Date *l=new Date();
    l->setScale((ui->reportDisplay->width()-50)/A4_X);
    elemList->add(l);
    elemList->print(scene);
}

void ReportDialog::on_comButton_clicked(){
    CommentElem *ce = new CommentElem(QInputDialog::getText(this,"Texte Libre" , "Entrez le texte :"), (ui->reportDisplay->width() -50)/A4_X);
    ce->setScale((ui->reportDisplay->width()-50)/A4_X);
    elemList->add(ce);
    elemList->print(scene);
}

void ReportDialog::on_nameButton_clicked(){

    NameElem *l=new NameElem();
    l->setScale((ui->reportDisplay->width()-50)/A4_X);
    elemList->add(l);
    elemList->print(scene);
}

void ReportDialog::on_removeButton_clicked(){
	delete elemList->remove();
	elemList->print(scene);
}

void ReportDialog::on_comLineButton_clicked(){

    LigneCom *l=new LigneCom(QInputDialog::getText(this , "Ajout d'une ligne de commentaire" , "Entrez votre commentaire :"));
    l->setScale((ui->reportDisplay->width()-50)/A4_X);
    elemList->insert(l);
    elemList->print(scene);
}

void ReportDialog::on_addLineButton_clicked(){
    Ligne *l=new Ligne();
    l->setScale((ui->reportDisplay->width()-50)/A4_X);
    elemList->insert(l);
	elemList->print(scene);
}

void ReportDialog::on_addPicButton_clicked(){
    Photo *p = new Photo(QFileDialog::getOpenFileName ( 0, "Get photo", "Snapshots" ,
                                                       "Images (*.jpg *.png *.gif)")) ;
    p->setScale((ui->reportDisplay->width()-50)/A4_X);
    elemList->insert(p);
	elemList->print(scene);
}

void ReportDialog::on_addTitleButton_clicked(){
	QStringList encart;
    encart << "Caractéristique" << "Mesure" << "Nominal" << "Tol+" << "Tol-"<< "Dév/Hors Tol" ;
    LigneText *lt = new LigneText(encart,"E",true);
    lt->setScale((ui->reportDisplay->width()-50)/A4_X);
    elemList->insert(lt);
	elemList->print(scene);
}

void ReportDialog::on_printButton_clicked(){
    elemList->print(false);
}

void ReportDialog::on_pdfButton_clicked(){
    elemList->print();
}

void ReportDialog::on_saveButton_clicked(){
    QString newItem = elemList->save().split("/").back();
    if(ui->canvasComboBox->findText(newItem)==-1 && newItem != "")
        ui->canvasComboBox->addItem(newItem);
}

void ReportDialog::on_suprButton_clicked(){
    int i = ui->canvasComboBox->currentIndex();
    if(i==0) return;
    QString Item = ui->canvasComboBox->currentText();
    int rep = QMessageBox::question(this, "Suppression modèle" , "Voulez vous vraiment supprimer le modèle " + Item , QMessageBox::Ok|QMessageBox::Cancel);
    if(rep == QMessageBox::Cancel) return;
    ui->canvasComboBox->removeItem(i);
    QDir Can("Canvas");
    Can.cd(Item);
    QStringList list = Can.entryList(QDir::AllEntries);
    for(int j = 0 ; j < list.size() ; j++)
        Can.remove(list[j]);
    Can.cdUp();
    Can.rmdir(Item);

}

void ReportDialog::on_fontIncButton_clicked(){
    elemList->setFont(QApplication::font() , 2);
}

void ReportDialog::on_fontDecButton_clicked(){
    elemList->setFont(QApplication::font() , 3);
}

void ReportDialog::on_fontComboBox_currentIndexChanged(QString name){
    elemList->setFont(QFont(name), 1);
}


void ReportDialog::on_fontAugButton_clicked(){
    elemList->setFont(QApplication::font() , 2,true);
}

void ReportDialog::on_fontRedButton_clicked(){
    elemList->setFont(QApplication::font() , 3,true);
}

void ReportDialog::on_fontComboBox_2_currentIndexChanged(QString name){
    elemList->setFont(QFont(name), 1,true);
}



void ReportDialog::on_boldCheckBox_stateChanged(int state){
    elemList->setBold((state !=0));
}

void ReportDialog::setReport(QString filename , QString logo){
    ui->canvasComboBox->setCurrentIndex(0);
    donnees = new Report(filename , logo);
    elemList->clear();
    donnees->print(elemList , scene);
}


void ReportDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ReportDialog::keyPressEvent(QKeyEvent *event)
{
    QDialog::keyPressEvent(event);
    elemList->print(scene);
}

void ReportDialog::resizeEvent ( QResizeEvent * event){
    elemList->setScale(ui->reportDisplay->width());
    QDialog::resizeEvent ( event );
    elemList->print(scene);
}



