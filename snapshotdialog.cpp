#include "snapshotdialog.h"
#include "ui_snapshotdialog.h"
#include <QPushButton>

SnapshotDialog::SnapshotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SnapshotDialog)
{
    ui->setupUi(this);
	connect(this , SIGNAL(accepted()) , this , SLOT(onAccepted()));
	this->setWindowOpacity(0.4);
    this->setModal(true);
}

SnapshotDialog::~SnapshotDialog()
{
    delete ui;
}

void SnapshotDialog::onAccepted()
{
    emit snapshotZoneChoosen(this->frameGeometry());
}

