#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //vtkSmartPointer<vtkActor> actor;
    //vtkSmartPointer<vtkRenderer> renderer;

public slots:
    void handleModelButton();
    void handleBackgButton();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
