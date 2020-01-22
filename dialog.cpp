#include "dialog.h"
#include "ui_dialog.h"
#include <QFile>
#include <QStringList>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QDebug>
#include <QFont>
#include <QRect>
#include <QDesktopWidget>
#include <Windows.h>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Tangyin"));
    this->resize(600,520);

    ui->te_input->setFocus();
    ui->te_article->setReadOnly(true);
    ui->lbl_info->setText(tr("Tanyin version 1.0, developed by Shijie Xu, contact me with <a href=\"xushijie.cn@gmail.com\">xushijie.cn@gmail.com</a>"));
    ui->lbl_speed->setText(tr("Escaped Time: 0 s, Speed: 0 w/s"));

    tackle_dict();
    tackle_text();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::tackle_dict()
{
    QFile in("C:/Users/Shijie Xu/Documents/LookUpPingShuiYun/dict.txt");
    if(!in.open(QFile::ReadOnly|QFile::Text))QMessageBox::warning(this, tr("Warning"), tr("Cannot open dict.txt!"));
    QString content = in.readAll();
    codes = content.split("\n");
    for(int i=0;i<codes.count();i++){
        QString code = codes.at(i);
        QStringList tmp_code = code.split("\t");
//        qDebug() << code << tmp_code;
        if (tmp_code.count()>1)
                mapDict.insert(tmp_code.at(0), tmp_code.at(1));
    }
}

void Dialog::tackle_text()
{
    QFile text("C:/Users/Shijie Xu/Documents/LookUpPingShuiYun/text.txt");
    if(!text.open(QFile::ReadOnly|QFile::Text))QMessageBox::warning(this, tr("Warning"), tr("Cannot open Text file!"));
    QString content = text.readAll();
    QStringList list = content.split("\n");
    int ch = QRandomGenerator::global()->bounded(list.count());
    ui->te_article->setText(list.at(ch));

    QString word = ui->te_article->toPlainText().at(0);
    ui->lbl_hint->setText(tr("%1 <font color=\"blue\">%2</font>").arg(word).arg(mapDict[word]));
}


void Dialog::on_pushButton_clicked()
{
    dlgShowTable *new_dlg = new dlgShowTable(this);
    new_dlg->show();
//    new_dlg->setModal(false);
    int nWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    int nHeight = GetSystemMetrics(SM_CYFULLSCREEN);
    new_dlg->move(0,0);
    new_dlg->resize(nWidth/2, nHeight);
    new_dlg->setWindowTitle(tr("Keyboard Layout for middle Chinese: C+S+V"));

    ui->pushButton->setEnabled(false);
    connect(new_dlg, &dlgShowTable::close_dlg, this, &Dialog::reenable_button);
}

bool Dialog::reenable_button()
{
    ui->pushButton->setEnabled(true);
    return true;
}

void Dialog::on_te_input_textChanged()
{
    QString type_text = ui->te_input->toPlainText();
    QString original_text = ui->te_article->toPlainText();
    // if completed
    if (type_text==original_text)QMessageBox::information(
                this, tr("Information"),tr("You completed the article, cong!")
                );

    // compared with original text
    int i = 0;
    while(i<type_text.count() && i<original_text.count()){
        if(type_text.at(i)==original_text.at(i)){
            i++;
        }else{
            break;
        }
    }
    QTextCursor cur = ui->te_input->textCursor();
    cur.setPosition(i);
    ui->te_input->setTextCursor(cur);
    ui->lbl_info->setText(tr("You typed %1 words correct.").arg(i));

    // set current word
    show_hint(original_text.at(i));

    if (!is_timer_started){
        timer.start(1000);
        connect(&timer, &QTimer::timeout, this, &Dialog::update_speed);
        start_time = time(NULL);
    }

}

void Dialog::show_hint(QString word)
{
    ui->lbl_hint->setText(tr("%1 <font color=\"blue\">%2</font>").arg(word).arg(mapDict[word]));
}

void Dialog::on_pushButton_2_clicked()
{
    if(!is_full_screen){
//        QRect screenRect = QApplication::desktop()->screenGeometry();
//        int nWidth = screenRect.width();
//        int nHeight = screenRect.height();
        int nWidth = GetSystemMetrics(SM_CXFULLSCREEN);
        int nHeight = GetSystemMetrics(SM_CYFULLSCREEN);

        this->old_pos = this->pos();
        this->old_size = this->size();
        this->is_full_screen = true;
        this->resize(nWidth/2, nHeight);
        this->move(nWidth/2, 0);
        ui->pushButton_2->setText(tr("Exit"));
    }else{
        this->resize(old_size);
        this->move(old_pos);
        this->is_full_screen = false;
        ui->pushButton_2->setText(tr("Fullscreen"));
    }
}

void Dialog::on_btn_mini_clicked()
{
    miniDlg *mini = new miniDlg(this);
    mini->setup_dict(this->mapDict);
    this->hide();
    connect(mini, &miniDlg::close_dlg, this, &Dialog::recovery_dlg);
    mini->show();
}

void Dialog::recovery_dlg()
{
    this->show();
}

void Dialog::update_speed()
{
    int word_count = ui->te_input->toPlainText().count();
    int secs = time(NULL) - start_time;
    ui->lbl_speed->setText(tr("Escaped Time: %1 s, Speed: %2 w/s").arg(secs).arg((float)word_count/secs));
}
