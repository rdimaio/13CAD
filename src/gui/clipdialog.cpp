#include "clipdialog.h"
#include "ui_clipdialog.h"
#include "mainwindow.h"

ClipDialog::ClipDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClipDialog)
{
    ui->setupUi(this);
    
    connect(ui->xSlider, SIGNAL(sliderMoved(int)), this, SLOT(on_xSlider_sliderMoved(int)));
    connect(ui->ySlider, SIGNAL(sliderMoved(int)), this, SLOT(on_ySlider_sliderMoved(int)));
    connect(ui->zSlider, SIGNAL(sliderMoved(int)), this, SLOT(on_zSlider_sliderMoved(int)));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(on_clipDialog_rejected()));
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

void ClipDialog::on_clipDialog_rejected()
{
    emit clipDialogRejected();
}