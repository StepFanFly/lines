#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>

namespace Ui {
class setupDialog;
}

class setupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit setupDialog(QWidget *parent = 0);
    ~setupDialog();
protected:
    void showEvent(QShowEvent * event);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::setupDialog *ui;
    int num_x;
    int num_y;
    int next_n;//new balls count
    int colors;//how many colors
    int in_line;//how many balls in line
signals:
    void on_accepted(int x, int y, int next_n, int colors, int in_line);
    void on_rejected();
    void omg_hide();
};

#endif // SETUPDIALOG_H
