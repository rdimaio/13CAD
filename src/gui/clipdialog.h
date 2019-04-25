/**
 * @file clipdialog.h
 * @brief Header file for the clip filter dialog
 * @author Riccardo DI Maio
 * @version 1.0 24/04/19
 */

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
    void xDialMoved(int value);
    void yDialMoved(int value);
    void zDialMoved(int value);
    void clipDialogRejected();
    void clipDialogAccepted();

public:
    explicit ClipDialog(QWidget *parent = nullptr);
    ~ClipDialog();

private slots:
    void on_xSlider_sliderMoved(int position);
    void on_ySlider_sliderMoved(int position);
    void on_zSlider_sliderMoved(int position);
    void on_xDial_sliderMoved(int position);
    void on_yDial_sliderMoved(int position);
    void on_zDial_sliderMoved(int position);
    void on_clipDialog_rejected();
    void on_clipDialog_accepted();

private:
    Ui::ClipDialog *ui;
};

#endif // CLIPDIALOG_H
