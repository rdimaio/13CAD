/**
 * @file clipdialog.h
 * @brief Header file for the clip filter dialog
 * @author Riccardo DI Maio
 * @version 1.0 24/04/19
 */

#ifndef CLIPDIALOG_H
#define CLIPDIALOG_H

#include <QDialog>

namespace Ui
{
class ClipDialog;
}

/**
 * Clip filter dialog.
 * As MainWindow cannot access ClipDialog's objects (e.g. xSlider, yDial)
 * directly, custom signals are used to be emitted and picked up by MainWindow.
 */
class ClipDialog : public QDialog
{
    Q_OBJECT

  signals:
    /**
     * Signal emitted when the x slider is moved
     */
    void xSliderMoved(int value);
    /**
     * Signal emitted when the y slider is moved
     */
    void ySliderMoved(int value);
    /**
     * Signal emitted when the z slider is moved
     */
    void zSliderMoved(int value);
    /**
     * Signal emitted when the x dial is moved
     */
    void xDialMoved(int value);
    /**
     * Signal emitted when the y dial is moved
     */
    void yDialMoved(int value);
    /**
     * Signal emitted when the z dial is moved
     */
    void zDialMoved(int value);
    /**
     * Signal emitted when the OK button is clicked
     */
    void clipDialogRejected();
    /**
     * Signal emitted when the Cancel button is clicked
     */
    void clipDialogAccepted();

  public:
    explicit ClipDialog(QWidget *parent = nullptr);
    ~ClipDialog();

  private slots:
    /**
     * Slot handling the sliderMoved signal from the x slider
     */
    void on_xSlider_sliderMoved(int position);
    /**
     * Slot handling the sliderMoved signal from the y slider
     */
    void on_ySlider_sliderMoved(int position);
    /**
     * Slot handling the sliderMoved signal from the z slider
     */
    void on_zSlider_sliderMoved(int position);
    /**
     * Slot handling the sliderMoved signal from the x dial
     */
    void on_xDial_sliderMoved(int position);
    /**
     * Slot handling the sliderMoved signal from the y dial
     */
    void on_yDial_sliderMoved(int position);
    /**
     * Slot handling the sliderMoved signal from the z dial
     */
    void on_zDial_sliderMoved(int position);
    /**
     * Slot handling the OK button
     */
    void on_clipDialog_accepted();
    /**
     * Slot handling the Cancel button
     */
    void on_clipDialog_rejected();

  private:
    Ui::ClipDialog *ui;
};

#endif // CLIPDIALOG_H
