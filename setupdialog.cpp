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
