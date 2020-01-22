#include "minidlg.h"
#include "ui_minidlg.h"
#include <Windows.h>
#include <QCloseEvent>

miniDlg::miniDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::miniDlg)
{
    ui->setupUi(this);

    ui->lbl_search->setText(tr("NaN"));

    this->setWindowTitle(tr("Search word"));
    this->resize(400,10);
    int nWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    this->move(nWidth - 400, 0);

    ui->le_search->setFocus();
}

miniDlg::~miniDlg()
{
    delete ui;
}

void miniDlg::setup_dict(QMap<QString, QString> dict)
{
    mapDict = dict;
}

void miniDlg::on_le_search_returnPressed()
{
    QString word = ui->le_search->text();
    if(mapDict.contains(word)){
        ui->lbl_search->setText(mapDict[word].toUpper());
    }else{
        ui->lbl_search->setText(tr("NaN"));
    }
}

void miniDlg::on_btn_recovery_normal_mode_clicked()
{
    this->close();
    emit close_dlg();
}

void miniDlg::closeEvent(QCloseEvent *e)
{
    emit close_dlg();
}
