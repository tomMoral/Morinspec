#ifndef REPORTDIALOG_H
#define REPORTDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QGraphicsScene>
#include "report.h"
#include "elemlist.h"

namespace Ui {
    class ReportDialog;
}

class ReportDialog : public QDialog {
    Q_OBJECT
public:
    ReportDialog(QWidget *parent = 0);
    ~ReportDialog();
    void setReport(QString filename , QString logo);

public slots:
	void on_canvasComboBox_currentIndexChanged(QString text);
	void on_dateButton_clicked();
    void on_comButton_clicked();
	void on_nameButton_clicked();
	void on_removeButton_clicked();
    void on_comLineButton_clicked();
	void on_addLineButton_clicked();
	void on_addPicButton_clicked();
	void on_addTitleButton_clicked();
    void on_printButton_clicked();
    void on_pdfButton_clicked();
	void on_saveButton_clicked();
    void on_suprButton_clicked();
    void on_fontIncButton_clicked();
    void on_fontDecButton_clicked();
    void on_fontComboBox_currentIndexChanged(QString name);
    void on_fontAugButton_clicked();
    void on_fontRedButton_clicked();
    void on_fontComboBox_2_currentIndexChanged(QString name);
    void on_boldCheckBox_stateChanged(int state);


protected:
    void changeEvent(QEvent *e);
    void keyPressEvent(QKeyEvent * event);
    void resizeEvent ( QResizeEvent * event );
private:
    Ui::ReportDialog *ui;
    Report *donnees;
    QGraphicsScene *scene;
	ElemList *elemList;
    bool control;
    QList<int> indexes;
};

#endif // REPORTDIALOG_H
