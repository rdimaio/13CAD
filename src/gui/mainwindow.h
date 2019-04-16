#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>
#include <QGuiApplication>
#include <QColorDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void handleOpenButton();
//    void handleModelButton();
//    
//    void handleBackgButton();
//
//private slots:
//    void on_sa_clicked();
//    
//    void on_greenButton_clicked();
//
//    void on_actionFileOpen_triggered();
//
//    void on_horizontalSlider_sliderMoved(int position);
//
//    void on_horizontalSlider_2_sliderMoved(int position);
//
//    void on_horizontalSlider_3_sliderMoved(int position);
//
//    void on_actionFileSave_triggered();
//
//    void on_actionHelp_triggered();
//
//    void on_actionPrint_triggered();

private:
    Ui::MainWindow *ui;
};

void LoadModel(std::string inputFilename);

#endif // MAINWINDOW_H
