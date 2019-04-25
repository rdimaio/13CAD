/**
 * @file helpdialog.cpp
 * @brief Source file for the help dialog
 * @author Riccardo Di Maio
 * @version 1.0 22/04/19
 */

#include "helpdialog.h"
#include "ui_helpdialog.h"

HelpDialog::HelpDialog(QWidget *parent) : QDialog(parent),
                                          ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
}

HelpDialog::~HelpDialog()
{
    delete ui;
}
