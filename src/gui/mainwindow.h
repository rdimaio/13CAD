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
#include <QInputDialog>
#include <QLineEdit>
#include <QString>
#include <QAction>
#include <QActionGroup>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    

private:
    Ui::MainWindow *ui;
    void setupWindow();
    void setupButtons(bool modelLoaded);
    void setupConnects();
    /**
    * Loads model.
    */
    void loadModel(QString inputFilename);
    /**
     * Clears loaded model.
    */
    void clearModel();

    void resetCamera();

public slots:
    void handleActionOpen();
    void handleActionSave();
    void handleActionClose();
    void handleActionPrint(); // Handles actionScreenshot too
    void handleActionStlTest();
    void handleActionModTest();

private slots:
    // Properties
    void on_bkgColourButton_clicked();
    void on_gradientCheckBox_stateChanged(int state);
    void on_modColourButton_clicked();
    void on_resetPropertiesButton_clicked();

    // Lighting
    // Note on opacity slider:
    // If a STL model is loaded, there is only one actor,
    // thus changing the opacity as the slider is moved
    // is not resource expensive.
    // If a MOD model is loaded, there will be many actors,
    // thus the opacity is only changed when the value is changed.
    void on_opacitySlider_sliderMoved(int position);
    void on_opacitySlider_valueChanged(int value);

    void on_specularitySlider_sliderMoved(int position);
    void on_specularitySlider_valueChanged(int value);

    void on_intensitySlider_sliderMoved(int position);
    void on_lightCheckBox_stateChanged(int state);

    void on_resetLightingButton_clicked();

    // Camera
    // Note for the camera functions:
    // The view up vector must be set to be orthogonal to the camera direction.
    void on_resetCameraButton_clicked();
    void on_posXButton_clicked();
    void on_posYButton_clicked();
    void on_posZButton_clicked();
    void on_pos90Button_clicked();
    void on_negXButton_clicked();
    void on_negYButton_clicked();
    void on_negZButton_clicked();
    void on_neg90Button_clicked();

    // Visualization
    void on_wireframeRadio_toggled(bool checked);
    void on_pointsRadio_toggled(bool checked);
    void on_surfaceRadio_toggled(bool checked);
};

#endif // MAINWINDOW_H
