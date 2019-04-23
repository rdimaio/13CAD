#include "clipdialog.h"
#include "ui_clipdialog.h"

ClipDialog::ClipDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClipDialog)
{
    ui->setupUi(this);
}

ClipDialog::~ClipDialog()
{
    delete ui;
}
