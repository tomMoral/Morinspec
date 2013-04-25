#include "reportermv.h"
#include "ui_reportermv.h"
#include <QDesktopWidget>
#include <QTextStream>
#include <QTime>

ReporterMV::ReporterMV(uint64_t computerName , QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReporterMV)
{

    qDebug() <<"Name :" <<  computerName << ":)";
    QFile licence("Licence.l");
    if(!licence.open(QIODevice::ReadOnly|QIODevice::Text)){
        licence.open((QIODevice::WriteOnly|QIODevice::Text));
        licence.write("0");
        licence.close();
        licence.open(QIODevice::ReadOnly|QIODevice::Text);
    }
    uint64_t l1 = licence.readLine().toInt();
    uint64_t l2 = l1;
    uint64_t key = computerName%125418539+54919373;
    licence.close();
    bool ok = false;

    while(key != l2){
        l2 = QInputDialog::getInt(0,"Licence" , "Entrée le numero de license associée à l'ordinateur : " + QString::number(computerName)
                                  ,0 ,-2147483647 , 2147483647 , 1 , &ok);
        if(!ok){
            showed = false;
            reportDialog = NULL;
            snapDialog = NULL;
            return;
        }
    }
    showed = true;

    if(l1!=l2){
        licence.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate);
        licence.write(QString::number(l2).toStdString().c_str());
    }




    ui->setupUi(this);
    reportDialog = new ReportDialog();
    snapDialog = new SnapshotDialog(this);
    paramDialog = new ParamDialog(this);
    connect(snapDialog , SIGNAL(snapshotZoneChoosen(QRect)) , this , SLOT(changeSnapZoneParam(QRect)));
    connect(paramDialog , SIGNAL(logoButtonS()) , this , SLOT(logoButton()));
    connect(paramDialog , SIGNAL(exportButtonS()) , this , SLOT(exportButton()));
    connect(paramDialog , SIGNAL(snapZoneButtonS()) , this , SLOT(paramSnapButton()));

    //Load initial param
    QFile paramConfig("paramConfig.ini");
	if(!paramConfig.open(QIODevice::ReadOnly|QIODevice::Text)){
		exportDir = "";
        this->paramSnapshot = QRect(10,10,200,100);
        QMessageBox::information(this,"Configuration Initiale" , "Configuration du dossier d'exportation (dossier où vous exportez vos fichiers *.txt");
        this->exportButton();
        QMessageBox::information(this,"Configuration Initiale" , "Configuration du logo que vous voulez pour les rapports");
        this->logoButton();
        QMessageBox::information(this,"Configuration Initiale" , "Configuration de la fenetre de capture d'ecran.\nRedimensionnez la fenetre transparente pour qu'elle epouse les bords de la zone de schema de Inspec");
        this->paramSnapButton();
	}
    else{
        QTextStream in(&paramConfig);
        int x,y,width,height;
        char waste;
        in >> x >>waste >> y >> waste >> width >> waste >> height >> waste >> exportDir >> waste >> logo;
        paramConfig.close();
        this->paramSnapshot = QRect(x , y, width , height);
    }

}

ReporterMV::~ReporterMV()
{
    delete reportDialog;
    delete snapDialog;
    delete ui;
}

void ReporterMV::on_SnapshotButton_clicked()
{
    //Capture de la zone schema de inspec
	this->hide();
	QTime dieTime = QTime::currentTime().addMSecs(250);
	while(QTime::currentTime() < dieTime){ }
    QPixmap originalPixmap =
            QPixmap::grabWindow(QApplication::desktop()->winId() ,
                                paramSnapshot.x() , paramSnapshot.y(),
                                paramSnapshot.width() , paramSnapshot.height());
	QDir snapDir("Snapshots");
	int n = snapDir.entryList(QDir::Files).size();
	originalPixmap.save(QString("Snapshots/Snapshots")+ QString::number(n) + ".png" , "png" , 100);
	originalPixmap =originalPixmap.scaled(155,57);
	this->show();
    QMessageBox::information(this , "Capture d'ecran" , "La capture a été enregistrée.");
}


void ReporterMV::on_EditButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Edit Report" , exportDir , "*.txt");
    if(filename.isNull())
        return;

    reportDialog->setReport(filename , logo);
    reportDialog->show();
    //reportDialog->resize(QApplication::desktop()->rect().size()-QSize(10,50));

    reportDialog->setGeometry(QRect(QApplication::desktop()->pos()+QPoint(20,30),QApplication::desktop()->rect().size()-QSize(40,60)));
    reportDialog->resize(QApplication::desktop()->rect().size()-QSize(30,80));
}

void ReporterMV::on_paramButton_clicked()
{
    paramDialog->show();
}
void ReporterMV::on_cleanSnapButton_clicked()
{
    QDir snap("Snapshots");
    QStringList list = snap.entryList(QDir::Files);
    for(int i = 0 ; i < list.size() ; i++)
        snap.remove(list[i]);
}

void ReporterMV::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

//Configuration des paramètres


void ReporterMV::logoButton()
{
    //Definie un dossier d'exportation et le stocke dans les paramètres .ini
    bool ok = false;
    QString logoF = "";
    QString fileName = "";
    while(!ok){
        logoF = QFileDialog::getOpenFileName(0,"Logo", "./","Images (*.jpg *.png *.gif)");

        fileName = logoF.split('/').back();
        ok = true;
        if(QDir::current().exists(fileName) && logoF != (QDir::currentPath() + "/" + fileName) ){
            int i = QMessageBox::warning(0,"Alert" , QString("Voulez vous écraser le modèle ") + fileName + "?" ,
                                 QMessageBox::Save|QMessageBox::Cancel,QMessageBox::Cancel);
            ok = (i==QMessageBox::Save);
        }
    }
    if(logoF == "") return;
    logo = QDir::currentPath() + "/" + fileName;
    if(logo != logoF)
        QDir::current().remove(fileName);
    if(!QFile::copy(logoF , logo))
        qDebug() << "ERROR 112";
    QFile paramConfig("paramConfig.ini");
    if(paramConfig.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&paramConfig);
        out << paramSnapshot.x()<< ":";
        out << paramSnapshot.y() << ":";
        out << paramSnapshot.width() << ":";
        out << paramSnapshot.height() << endl;
        out << exportDir << endl;
        out << logo;
        paramConfig.close();
    }
}

void ReporterMV::exportButton()
{
    //Definie un dossier d'exportation et le stocke dans les paramètres .ini
    exportDir = QFileDialog::getExistingDirectory(0,"Dossier d'exportation" , exportDir);


    QFile paramConfig("paramConfig.ini");
    if(paramConfig.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&paramConfig);
        out << paramSnapshot.x()<< ":";
        out << paramSnapshot.y() << ":";
        out << paramSnapshot.width() << ":";
        out << paramSnapshot.height() << endl;
        out << exportDir << endl;
        out << logo;
        paramConfig.close();
    }
}

void ReporterMV::paramSnapButton()
{
    snapDialog->move(paramSnapshot.x(),paramSnapshot.y());
    snapDialog->resize(paramSnapshot.width() , paramSnapshot.height());
    snapDialog->show();
    this->hide();
    this->paramDialog->hide();
}

void ReporterMV::changeSnapZoneParam(QRect rectSS)
{
    this->paramSnapshot = rectSS;
    //On enregistre les paramètres dans un fichier ==> param réutilisable
    QFile paramConfig("paramConfig.ini");
    if(paramConfig.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&paramConfig);
        out << paramSnapshot.x()<< ":";
        out << paramSnapshot.y() << ":";
        out << paramSnapshot.width() << ":";
        out << paramSnapshot.height() << endl;
        out << exportDir << endl;
        out << logo;
        paramConfig.close();
    }
    this->show();
    this->paramDialog->show();
}
