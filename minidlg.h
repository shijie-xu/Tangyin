#ifndef MINIDLG_H
#define MINIDLG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class miniDlg;
}

class miniDlg : public QDialog
{
    Q_OBJECT

public:
    explicit miniDlg(QWidget *parent = nullptr);
    ~miniDlg();

public:
    void setup_dict(QMap<QString,QString> dict);

private slots:
    void on_le_search_returnPressed();

    void on_btn_recovery_normal_mode_clicked();

private:
    Ui::miniDlg *ui;

    QMap<QString,QString> mapDict;

signals:
    void close_dlg();

protected:
    void closeEvent(QCloseEvent *) override;
};

#endif // MINIDLG_H
