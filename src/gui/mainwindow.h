/**
 * @file mainwindow.h
 * @brief Header file for the graphical user interface code
 * @author Riccardo Di Maio
 * @version 1.0 15/03/19
 */

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

#include "clipdialog.h"

namespace Ui {
    class MainWindow;
}

/**
 * Main GUI window.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    ClipDialog *clipWindow = nullptr;

  signals:

    /**
     * Signal emitted when a message is displayed in the status bar
     */
    void statusUpdateMessage(const QString &message, int timeout);

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private:

    Ui::MainWindow *ui;

    /**
     * Setup function for the window
     */
    void setupWindow();

    /**
     * Setup function that handles which buttons are enabled when the model is loaded
     */
    void setupButtons(bool modelLoaded);

    /**
     * Setup function that connects icons to their respective QActions
     */
    void setupIcons();

    /**
     * Setup function that connects signals to their respective slots
     */
    void setupConnects();

    /**
     * Loads model
     */
    void loadModel(QString inputFilename);

    /**
     * Clears loaded model
     */
    void clearModel();

    /**
     * Resets camera
     */
    void resetCamera();

  public slots:

    /**
     * Handles file opening
     */
    void handleActionOpen();

    /**
     * Handles file saving
     */
    void handleActionSave();

    /**
     * Handles file closing
     */
    void handleActionClose();

    /**
     * Handles the screenshot function
     */
    void handleActionPrint();

    /**
     * Handles the toggling of external light
     */
    void handleActionEnableIntensity();

    /**
     * Handles the toggling of the coordinate axes
     */
    void handleActionShowAxes();

    /**
     * Handles the full screen function
     */
    void handleActionFullScreen();

    /**
     * Handles the export data function
     */
    void handleActionExportData();

    /**
     * Handles the about function, creates help dialog
     */
    void handleActionAbout();

    /**
     * Handles the reset filters function
     */
    void handleActionResetFilters();

    /**
     * Handles the reset camera function
     */
    void handleActionResetCamera();

    /**
     * Handles the reset lighting function
     */
    void handleActionResetLighting();

    /**
     * Handles the reset properties function
     */
    void handleActionResetProperties();

    /**
     * Loads a test .STL file
     */
    void handleActionStlTest();

    /**
     * Loads a test .mod file
     */
    void handleActionModTest();

  private slots:

    // Filters

    /**
     * Enables shrink filter
     */
    void on_shrinkButton_clicked();

    /**
     * Enables clip filter
     */
    void on_clipButton_clicked();

    /**
     * Resets filters
     */
    void on_resetFiltersButton_clicked();

    // Properties

    /**
     * Shows colour dialog, allows the user to change background colour
     */
    void on_bkgColourButton_clicked();

    /**
     * Toggle between gradient and non-gradient background
     */
    void on_gradientCheckBox_stateChanged(int state);

    /**
     * Shows colour dialog, allows the user to change model colour
     */
    void on_modColourButton_clicked();

    /**
     * Resets colours
     */
    void on_resetPropertiesButton_clicked();

    // Lighting
    // Note on opacity and specularity sliders:
    // If a STL model is loaded, there is only one actor,
    // thus changing the opacity as the slider is moved
    // is not resource expensive.
    // If a MOD model is loaded, there will be many actors,
    // thus the opacity is only changed when the value is changed.

    /**
     * Changes opacity of .stl models as the slider is moved
     */
    void on_opacitySlider_sliderMoved(int position);

    /**
     * Changes opacity of .mod models after the slider is released
     */
    void on_opacitySlider_valueChanged(int value);

    /**
     * Changes specularity of .stl models as the slider is moved
     */
    void on_specularitySlider_sliderMoved(int position);

    /**
     * Changes specularity of .mod models after the slider is released
     */
    void on_specularitySlider_valueChanged(int value);

    /**
     * Changes intensity of external light as the slider is moved
     */
    void on_intensitySlider_sliderMoved(int position);

    /**
     * Toggles external light
     */
    void on_intensityCheckBox_stateChanged(int state);

    /**
     * Toggles coordinate axes
     */
    void on_showAxesCheckBox_stateChanged(int state);

    /**
     * Resets lighting
     */
    void on_resetLightingButton_clicked();

    /**
     * Changes X parameter of clip plane for the clip filter
     */
    void on_clipXSlider_sliderMoved(int position);
    
    /**
     * Changes Y parameter of clip plane for the clip filter
     */
    void on_clipYSlider_sliderMoved(int position);
        
    /**
     * Changes Z parameter of clip plane for the clip filter
     */
    void on_clipZSlider_sliderMoved(int position);
        
    /**
     * Changes X parameter of the rotation of the clip plane for the clip filter
     */
    void on_clipXDial_sliderMoved(int position);
            
    /**
     * Changes Y parameter of the rotation of the clip plane for the clip filter
     */
    void on_clipYDial_sliderMoved(int position);
            
    /**
     * Changes Z parameter of the rotation of the clip plane for the clip filter
     */
    void on_clipZDial_sliderMoved(int position);
                    
    /**
     * Accepts new clip filter's parameters, closes clip dialog
     */
    void on_clipDialog_dialogAccepted();    

    /**
     * Resets clip filter's parameters to previous state
     */
    void on_clipDialog_dialogRejected();

    // Camera
    // Note for the camera functions:
    // The view up vector must be set to be orthogonal to the camera direction.
    /**
     * Resets camera
     */
    void on_resetCameraButton_clicked();

    /**
     * Sets camera on the X axis
     */
    void on_posXButton_clicked();

    /**
     * Sets camera on the Y axis
     */
    void on_posYButton_clicked();

    /**
     * Sets camera on the Z axis
     */
    void on_posZButton_clicked();

    /**
     * Rotates camera clockwise 90 degrees
     */
    void on_pos90Button_clicked();

    /**
     * Sets camera on the negative X axis
     */
    void on_negXButton_clicked();

    /**
     * Sets camera on the negative Y axis
     */
    void on_negYButton_clicked();

    /**
     * Sets camera on the negative Z axis
     */
    void on_negZButton_clicked();

    /**
     * Rotates camera counter-clockwise 90 degrees
     */
    void on_neg90Button_clicked();

    // Visualization

    /**
     * Toggles wireframe visualization
     */
    void on_wireframeRadio_toggled(bool checked);

    /**
     * Toggles points visualization
     */
    void on_pointsRadio_toggled(bool checked);

    /**
     * Toggles surface (default) visualization
     */
    void on_surfaceRadio_toggled(bool checked);
};

#endif // MAINWINDOW_H
