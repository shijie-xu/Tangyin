#ifndef DLGSHOWTABLE_H
#define DLGSHOWTABLE_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class dlgShowTable;
}

class dlgShowTable : public QDialog
{
    Q_OBJECT

public:
    explicit dlgShowTable(QWidget *parent = nullptr);
    ~dlgShowTable();
protected:
    void closeEvent(QCloseEvent*);
private:
    Ui::dlgShowTable *ui;
signals:
    void close_dlg();
};

#endif // DLGSHOWTABLE_H
