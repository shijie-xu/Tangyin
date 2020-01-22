#include "dlgshowtable.h"
#include "ui_dlgshowtable.h"

dlgShowTable::dlgShowTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgShowTable)
{
    ui->setupUi(this);
}

dlgShowTable::~dlgShowTable()
{
    delete ui;
}

void dlgShowTable::closeEvent(QCloseEvent *)
{
    emit close_dlg();
}
