#ifndef CLIPDIALOG_H
#define CLIPDIALOG_H

#include <QDialog>

namespace Ui {
class ClipDialog;
}

class ClipDialog : public QDialog
{
    Q_OBJECT

signals:
    void xSliderMoved(int value);
    void ySliderMoved(int value);
    void zSliderMoved(int value);
    void clipDialogRejected();
    void clipDialogAccepted();

public:
    explicit ClipDialog(QWidget *parent = nullptr);
    ~ClipDialog();

private slots:
    void on_xSlider_sliderMoved(int position);
    void on_ySlider_sliderMoved(int position);
    void on_zSlider_sliderMoved(int position);
    void on_clipDialog_rejected();
    void on_clipDialog_accepted();

private:
    Ui::ClipDialog *ui;
};

#endif // CLIPDIALOG_H
