/**
 * @file clipdialog.cpp
 * @brief Source file for the clip filter dialog
 * @author Riccardo Di Maio
 * @version 1.0 24/04/19
 */

#include "clipdialog.h"
#include "ui_clipdialog.h"
#include "mainwindow.h"

ClipDialog::ClipDialog(QWidget *parent) : QDialog(parent),
                                          ui(new Ui::ClipDialog)
{
    ui->setupUi(this);

    connect(ui->xSlider, SIGNAL(sliderMoved(int)), this, SLOT(on_xSlider_sliderMoved(int)));
    connect(ui->ySlider, SIGNAL(sliderMoved(int)), this, SLOT(on_ySlider_sliderMoved(int)));
    connect(ui->zSlider, SIGNAL(sliderMoved(int)), this, SLOT(on_zSlider_sliderMoved(int)));
    connect(ui->xDial, SIGNAL(sliderMoved(int)), this, SLOT(on_xDial_sliderMoved(int)));
    connect(ui->yDial, SIGNAL(sliderMoved(int)), this, SLOT(on_yDial_sliderMoved(int)));
    connect(ui->zDial, SIGNAL(sliderMoved(int)), this, SLOT(on_zDial_sliderMoved(int)));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(on_clipDialog_rejected()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(on_clipDialog_accepted()));
}

ClipDialog::~ClipDialog()
{
    delete ui;
}

void ClipDialog::on_xSlider_sliderMoved(int position)
{
    emit xSliderMoved(position);
}

void ClipDialog::on_ySlider_sliderMoved(int position)
{
    emit ySliderMoved(position);
}

void ClipDialog::on_zSlider_sliderMoved(int position)
{
    emit zSliderMoved(position);
}

void ClipDialog::on_xDial_sliderMoved(int position)
{
    emit xDialMoved(position);
}

void ClipDialog::on_yDial_sliderMoved(int position)
{
    emit yDialMoved(position);
}

void ClipDialog::on_zDial_sliderMoved(int position)
{
    emit zDialMoved(position);
}

void ClipDialog::on_clipDialog_rejected()
{
    emit clipDialogRejected();
}

void ClipDialog::on_clipDialog_accepted()
{
    emit clipDialogAccepted();
}