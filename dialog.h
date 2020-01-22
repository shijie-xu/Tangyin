#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "dlgshowtable.h"
#include "minidlg.h"
#include <QMap>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
    bool reenable_button();

    void on_te_input_textChanged();

    void on_pushButton_2_clicked();

    void on_btn_mini_clicked();

    void recovery_dlg();

    void update_speed();
private:
    Ui::Dialog *ui;

    QStringList codes;
    QMap<QString, QString> mapDict;

    QSize old_size;
    QPoint old_pos;
    bool is_full_screen = false;

    QTimer timer;
    bool is_timer_started = false;

    uint start_time;
public:
    void show_hint(QString word);
    void tackle_dict();
    void tackle_text();

};
#endif // DIALOG_H
