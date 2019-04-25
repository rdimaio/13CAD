/**
 * @file helpdialog.h
 * @brief Header file for the help dialog
 * @author Riccardo Di Maio
 * @version 1.0 22/04/19
 */

#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

namespace Ui{
    class HelpDialog;
}

class HelpDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit HelpDialog(QWidget *parent = nullptr);
    ~HelpDialog();

  private:
    Ui::HelpDialog *ui;
};

#endif // HELPDIALOG_H
