#ifndef PARAMDIALOG_H
#define PARAMDIALOG_H

#include <QDialog>

namespace Ui {
class ParamDialog;
}

class ParamDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ParamDialog(QWidget *parent = 0);
    ~ParamDialog();

public slots:
    void on_logoButton_clicked(){ emit logoButtonS();}
    void on_exportButton_clicked(){ emit exportButtonS();}
    void on_paramSnapButton_clicked(){ emit snapZoneButtonS();}

signals:
    void logoButtonS();
    void exportButtonS();
    void snapZoneButtonS();
    
private:
    Ui::ParamDialog *ui;
};

#endif // PARAMDIALOG_H
