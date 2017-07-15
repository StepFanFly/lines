#include "setupdialog.h"
#include "ui_setupdialog.h"

setupDialog::setupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setupDialog)
{
    ui->setupUi(this);
}

setupDialog::~setupDialog()
{
    delete ui;
}

void setupDialog::showEvent(QShowEvent * event){
    QDialog::showEvent(event);
    emit omg_hide();
}

void setupDialog::on_buttonBox_accepted()
{
    num_x=ui->y_spin->value();
    num_y=ui->x_spin->value();
    next_n=ui->new_spin->value();
    colors=ui->color_spin->value();
    in_line=ui->del_spin->value();
    emit on_accepted(num_x,num_y,next_n,colors,in_line);
}

void setupDialog::on_buttonBox_rejected()
{
    emit on_rejected();
}
