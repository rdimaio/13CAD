#ifndef CLIPDIALOG_H
#define CLIPDIALOG_H

#include <QDialog>

namespace Ui {
class ClipDialog;
}

class ClipDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClipDialog(QWidget *parent = nullptr);
    ~ClipDialog();

private:
    Ui::ClipDialog *ui;
};

#endif // CLIPDIALOG_H
