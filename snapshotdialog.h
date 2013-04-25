#ifndef SNAPSHOTDIALOG_H
#define SNAPSHOTDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
    class SnapshotDialog;
}

class SnapshotDialog : public QDialog {
    Q_OBJECT
public:
    SnapshotDialog(QWidget *parent = 0);
    ~SnapshotDialog();

public slots:
    void onAccepted();

signals:
    void snapshotZoneChoosen(QRect frame);

private:
    Ui::SnapshotDialog *ui;
};

#endif // SNAPSHOTDIALOG_H
