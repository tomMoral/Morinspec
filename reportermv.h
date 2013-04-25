#ifndef REPORTERMV_H
#define REPORTERMV_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QWaitCondition>
#include "snapshotdialog.h"
#include "paramdialog.h"
#include "reportdialog.h"

namespace Ui {
    class ReporterMV;
}

class ReporterMV : public QMainWindow {
    Q_OBJECT
public:
    ReporterMV(uint64_t computerName , QWidget *parent= 0);
    ~ReporterMV();
    bool showed;

public slots:
	void on_EditButton_clicked();
    void exportButton();
    void logoButton();
    void on_SnapshotButton_clicked();
    void paramSnapButton();
    void on_cleanSnapButton_clicked();
    void on_paramButton_clicked();
    void changeSnapZoneParam(QRect rect);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ReporterMV *ui;
    ReportDialog* reportDialog;
    SnapshotDialog *snapDialog;
    ParamDialog *paramDialog;
    QRect paramSnapshot;
    QString exportDir , logo;
};

#endif // REPORTERMV_H
