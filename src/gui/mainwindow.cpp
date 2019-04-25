/**
 * @file mainwindow.cpp
 * @brief Main Qt file for the graphical user interface code
 * @author Riccardo Di Maio
 * @version 1.0 15/03/19
 */

// VTK libraries
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPlane.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkLight.h>
#include <vtkAxesActor.h>
#include <vtkTransform.h>

// VTK libraries - cells
#include <vtkCellArray.h>
#include <vtkCellType.h>
#include <vtkPoints.h>
#include <vtkUnstructuredGrid.h>
#include <vtkTetra.h>
#include <vtkPyramid.h>
#include <vtkHexahedron.h>
#include <vtkMassProperties.h>

// VTK libraries - filters
#include <vtkTriangleFilter.h>
#include <vtkShrinkFilter.h>
#include <vtkClipDataSet.h>

// VTK libraries - STL reading
#include <vtkSTLReader.h>
#include <vtkPolyDataMapper.h>

// VTK libraries - Screenshot function
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>

// Qt headers
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpdialog.h"
#include "clipdialog.h"

// Local headers
#include "model.h"

// VTK global variables
// Create a VTK render window and a renderer
vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
// Create STL reader
vtkSmartPointer<vtkSTLReader> reader;
// Create colors
vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
// Setup the light
vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
// Setup axes
vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
// Setup clip plane
vtkSmartPointer<vtkClipDataSet> clipFilter;
vtkSmartPointer<vtkPlane> clipPlane;
float clipX = 0;
float clipY = 0;
float clipZ = 0;
float clipNormalX = -1;
float clipNormalY = 0;
float clipNormalZ = 0;
float prevClipX = 0;
float prevClipY = 0;
float prevClipZ = 0;
float prevClipNormalX = -1;
float prevClipNormalY = 0;
float prevClipNormalZ = 0;
// Initialise vectors for mappers and actors
// .mod files have an actor/mapper per cell,
// while .stl files only require one actor/mapper for the entire file
std::vector<vtkSmartPointer<vtkDataSetMapper>> mappers;
std::vector<vtkSmartPointer<vtkActor>> actors;
// Initialise vectors for .mod parsing
std::vector<vtkSmartPointer<vtkUnstructuredGrid>> unstructuredGrids;
std::vector<vtkSmartPointer<vtkTetra>> tetras;
std::vector<vtkSmartPointer<vtkPyramid>> pyras;
std::vector<vtkSmartPointer<vtkHexahedron>> hexas;
QString inputFileName;	// Global string for model's filename
bool modelLoaded = false; // Global flag that indicates a model is currently loaded
bool clipFilterEnabled = false;
bool clipWindowShown = false;

// Declare stats QStrings (needed as global strings for the export data function)
QString surfAreaString;
QString volumeString;
QString cellString;
QString pointString;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	clipWindow = new ClipDialog();

	this->setupWindow();

	// Setup light (but don't add it)
	light->SetLightTypeToCameraLight();
	light->SetIntensity(0.5);
	light->SetFocalPoint(1.875, 0.6125, 0);
	light->SetPosition(0.875, 1.6125, 1);

	// The axes are positioned with a user transform
	transform->Translate(1.0, 0.0, 0.0);
	axes->SetUserTransform(transform);

	ui->intensitySlider->setEnabled(false);
	ui->shrinkButton->setEnabled(false);
	ui->clipButton->setEnabled(false);
	ui->resetFiltersButton->setEnabled(false);

	// Setup the renderers's camera
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Azimuth(30);
	renderer->GetActiveCamera()->Elevation(30);
	renderer->ResetCameraClippingRange();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setupWindow()
{

	// standard call to setup Qt UI (same as previously)
	ui->setupUi(this);

	setupButtons(modelLoaded);
	setupIcons();
	setupConnects();

	setWindowTitle(tr("13CAD"));

	// Link the VTK render window to the QtVTK widget
	// (qvtkWidget is the name gave to QtVTKOpenGLWidget in Qt Creator)
	ui->qvtkWidget->SetRenderWindow(renderWindow);

	// Add the renderer to the render window
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
}

void MainWindow::setupIcons()
{
	ui->actionOpen->setIcon(QIcon(":/open"));
	ui->actionSave->setIcon(QIcon(":/save"));
	ui->actionClose->setIcon(QIcon(":/close"));
	ui->actionPrint->setIcon(QIcon(":/print"));
	ui->actionExportData->setIcon(QIcon(":/data"));
	ui->actionAbout->setIcon(QIcon(":/info"));
	ui->actionStlTest->setIcon(QIcon(":/stltest"));
	ui->actionModTest->setIcon(QIcon(":/modtest"));
	ui->actionFullScreen->setIcon(QIcon(":/fullscreen"));
}

void MainWindow::setupButtons(bool modelLoaded)
{
	// Greyed out if no model is loaded, enabled if model is loaded
	ui->actionSave->setEnabled(modelLoaded);
	ui->actionClose->setEnabled(modelLoaded);
	ui->actionPrint->setEnabled(modelLoaded);
	ui->actionExportData->setEnabled(modelLoaded);
	ui->modColourButton->setEnabled(modelLoaded);
	ui->gradientCheckBox->setChecked(true); // Initialize gradient on
	ui->intensityCheckBox->setEnabled(modelLoaded);
	ui->intensityCheckBox->setChecked(false); // Initialize ext. light off
	ui->surfaceRadio->setChecked(true);		  // Initialize surface visualization on
	ui->resetCameraButton->setEnabled(modelLoaded);
	ui->resetPropertiesButton->setEnabled(modelLoaded);
	ui->resetLightingButton->setEnabled(modelLoaded);
	ui->opacitySlider->setEnabled(modelLoaded);
	ui->opacitySlider->setValue(99); // Initialize slider at max value
	ui->specularitySlider->setEnabled(modelLoaded);
	ui->specularitySlider->setValue(49); // Initialize slider at half value
	ui->intensitySlider->setValue(49);   // Initialize slider at half value
	ui->posXButton->setEnabled(modelLoaded);
	ui->posYButton->setEnabled(modelLoaded);
	ui->posZButton->setEnabled(modelLoaded);
	ui->pos90Button->setEnabled(modelLoaded);
	ui->negXButton->setEnabled(modelLoaded);
	ui->negYButton->setEnabled(modelLoaded);
	ui->negZButton->setEnabled(modelLoaded);
	ui->neg90Button->setEnabled(modelLoaded);
	// Uncheck filter buttons
	ui->shrinkButton->setCheckable(true);
	ui->clipButton->setCheckable(true);
	ui->shrinkButton->setChecked(false);
	ui->clipButton->setChecked(false);
}

void MainWindow::setupConnects()
{
	connect(this, &MainWindow::statusUpdateMessage, ui->statusBar, &QStatusBar::showMessage);
	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(handleActionOpen()));
	connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(handleActionSave()));
	connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(handleActionClose()));
	connect(ui->actionPrint, SIGNAL(triggered()), this, SLOT(handleActionPrint()));
	connect(ui->actionFullScreen, SIGNAL(triggered()), this, SLOT(handleActionFullScreen()));
	connect(ui->actionExportData, SIGNAL(triggered()), this, SLOT(handleActionExportData()));
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(handleActionAbout()));
	connect(ui->actionResetFilters, SIGNAL(triggered()), this, SLOT(handleActionResetFilters()));
	connect(ui->actionResetCamera, SIGNAL(triggered()), this, SLOT(handleActionResetCamera()));
	connect(ui->actionResetLighting, SIGNAL(triggered()), this, SLOT(handleActionResetLighting()));
	connect(ui->actionResetProperties, SIGNAL(triggered()), this, SLOT(handleActionResetProperties()));
	connect(ui->actionStlTest, SIGNAL(triggered()), this, SLOT(handleActionStlTest()));
	connect(ui->actionModTest, SIGNAL(triggered()), this, SLOT(handleActionModTest()));
	connect(ui->actionShowAxes, SIGNAL(triggered()), this, SLOT(handleActionShowAxes()));
	connect(ui->actionEnableIntensity, SIGNAL(triggered()), this, SLOT(handleActionEnableIntensity()));
	connect(ui->gradientCheckBox, SIGNAL(stateChanged(int)), this, SLOT(on_gradientCheckBox_stateChanged(int)));
	connect(ui->intensityCheckBox, SIGNAL(stateChanged(int)), this, SLOT(on_intensityCheckBox_stateChanged(int)));
	connect(ui->showAxesCheckBox, SIGNAL(stateChanged(int)), this, SLOT(on_showAxesCheckBox_stateChanged(int)));
	connect(ui->wireframeRadio, SIGNAL(toggled(bool)), this, SLOT(on_wireframeRadio_toggled(bool)));
	connect(ui->pointsRadio, SIGNAL(toggled(bool)), this, SLOT(on_pointsRadio_toggled(bool)));
	connect(ui->surfaceRadio, SIGNAL(toggled(bool)), this, SLOT(on_surfaceRadio_toggled(bool)));
	connect(ui->opacitySlider, SIGNAL(sliderMoved(int)), this, SLOT(on_opacitySlider_sliderMoved(int)));
	connect(ui->opacitySlider, SIGNAL(valueChanged(int)), this, SLOT(on_opacitySlider_valueChanged(int)));
	connect(ui->specularitySlider, SIGNAL(sliderMoved(int)), this, SLOT(on_specularitySlider_sliderMoved(int)));
	connect(ui->specularitySlider, SIGNAL(valueChanged(int)), this, SLOT(on_specularitySlider_valueChanged(int)));
	connect(ui->intensitySlider, SIGNAL(sliderMoved(int)), this, SLOT(on_intensitySlider_sliderMoved(int)));
	connect(clipWindow, SIGNAL(xSliderMoved(int)), this, SLOT(on_clipXSlider_sliderMoved(int)));
	connect(clipWindow, SIGNAL(ySliderMoved(int)), this, SLOT(on_clipYSlider_sliderMoved(int)));
	connect(clipWindow, SIGNAL(zSliderMoved(int)), this, SLOT(on_clipZSlider_sliderMoved(int)));
	connect(clipWindow, SIGNAL(xDialMoved(int)), this, SLOT(on_clipXDial_sliderMoved(int)));
	connect(clipWindow, SIGNAL(yDialMoved(int)), this, SLOT(on_clipYDial_sliderMoved(int)));
	connect(clipWindow, SIGNAL(zDialMoved(int)), this, SLOT(on_clipZDial_sliderMoved(int)));
	connect(clipWindow, SIGNAL(clipDialogRejected()), this, SLOT(on_clipDialog_dialogRejected()));
	connect(clipWindow, SIGNAL(clipDialogAccepted()), this, SLOT(on_clipDialog_dialogAccepted()));
}

void MainWindow::loadModel(QString inputFilename)
{

	// Declare data to display in stats section
	double modSurfArea;
	double modVolume;
	int modCells;
	int modPoints;
	vtkSmartPointer<vtkPolyData> modPolyData;

	if (modelLoaded)
	{
		double modSurfArea = 0;
		double modVolume = 0;
		int modCells = 0;
		int modPoints = 0;
		modPolyData->Initialize();
	}

	// Convert QString to std::string
	std::string modelFileName = inputFileName.toUtf8().constData();
	// Load model
	// (maybe only do model mod1 in case it's a .mod file, remove isstl from model,
	// and check here, so that you don't construct a model in case it's stl.)
	Model mod1(modelFileName);

	if (mod1.getIsSTL())
	{
		// Allow user to select STL only filters
		ui->shrinkButton->setEnabled(true);
		ui->resetFiltersButton->setEnabled(true);
		ui->clipButton->setEnabled(true);

		actors.resize(1);
		mappers.resize(1);

		if (modelLoaded)
		{
			actors[0] = NULL;
			mappers[0] = NULL;
			reader = NULL;
			clearModel();
		}

		// Visualize
		reader = vtkSmartPointer<vtkSTLReader>::New();
		reader->SetFileName(modelFileName.c_str());
		reader->Update();

		// NOTE: datasetmapper is used instead of polydatamapper.
		// Try to switch back to polydatamapper if there are any bugs.

		//vtkSmartPointer<vtkPolyDataMapper> poly_mapper =
		//vtkSmartPointer<vtkPolyDataMapper>::New();
		//poly_mapper->SetInputConnection(reader->GetOutputPort());

		mappers[0] = vtkSmartPointer<vtkDataSetMapper>::New();
		mappers[0]->SetInputConnection(reader->GetOutputPort());

		actors[0] = vtkSmartPointer<vtkActor>::New();
		actors[0]->SetMapper(mappers[0]);
		actors[0]->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());
		actors[0]->GetProperty()->SetSpecular(0.5);
		actors[0]->GetProperty()->SetSpecularPower(5);

		// Get PolyData of model
		modPolyData = reader->GetOutput();

		// Get stats
		modCells = modPolyData->GetNumberOfPolys();
		modPoints = modPolyData->GetNumberOfPoints();

		// Use a triangle filter to obtain mass and surface area information
		vtkTriangleFilter *triangleFilter = vtkTriangleFilter::New();
		triangleFilter->SetInputConnection(reader->GetOutputPort());
		triangleFilter->Update();
		vtkMassProperties *massProperty = vtkMassProperties::New();
		massProperty->SetInputConnection(triangleFilter->GetOutputPort());
		massProperty->Update();
		modSurfArea = massProperty->GetSurfaceArea();
		modVolume = massProperty->GetVolume();

		// Define the strings to be shown in the stats area
		surfAreaString = QString::number(modSurfArea) + " m^2";
		volumeString = QString::number(modVolume) + " m^3";
		cellString = QString::number(modCells);
		pointString = QString::number(modPoints);

		renderer->AddActor(actors[0]);
		emit statusUpdateMessage(QString("Loaded STL model"), 0);
	}
	else
	{
		// Prevent user from selecting STL only filters
		ui->shrinkButton->setEnabled(false);
		ui->resetFiltersButton->setEnabled(false);
		ui->clipButton->setEnabled(false);

		int poly_count = 0;
		int tetra_count = 0;		// Number of tetrahedrons
		int pyra_count = 0;			// Number of pyramids
		int hexa_count = 0;			// Number of hexahedrons
		int last_used_point_id = 0; // ID of last point used
		// Get vector of cells from the model
		std::vector<Cell> modCells = mod1.getCells();

		// Get vector of materials
		std::vector<Material> modMaterials = mod1.getMaterials();

		// Resize to new model
		unstructuredGrids.resize(modCells.size());
		actors.resize(modCells.size());
		mappers.resize(modCells.size());

		vtkSmartPointer<vtkCellArray> cellArray = vtkSmartPointer<vtkCellArray>::New();
		vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

		if (modelLoaded)
		{
			unstructuredGrids.clear();
			actors.clear();
			mappers.clear();
			tetras.clear();
			pyras.clear();
			hexas.clear();
			cellArray->Reset();
			points->Reset();

			clearModel();
		}

		// For each cell
		for (std::vector<Cell>::iterator it = modCells.begin(); it != modCells.end(); ++it)
		{

			// Get vertices of the cell
			std::vector<Vector3D> cellVertices = it->getVertices();

			// Tetrahedron
			if (cellVertices.size() == 4)
			{
				tetras.resize(tetra_count + 1);

				// Insert vertices into vtkPoints vector
				for (int i = 0; i < 4; i++)
				{
					points->InsertNextPoint(cellVertices[i].getX(), cellVertices[i].getY(), cellVertices[i].getZ());
				}

				unstructuredGrids[poly_count] = vtkSmartPointer<vtkUnstructuredGrid>::New();
				unstructuredGrids[poly_count]->SetPoints(points);
				tetras[tetra_count] = vtkSmartPointer<vtkTetra>::New();

				// Set points to the tetra
				for (int i = 0; i < 4; i++)
				{
					tetras[tetra_count]->GetPointIds()->SetId(i, last_used_point_id + i);
				}
				last_used_point_id += 4;

				cellArray->InsertNextCell(tetras[tetra_count]);
				unstructuredGrids[poly_count]->SetCells(VTK_TETRA, cellArray);
				tetra_count++;

				// Pyramid
			}
			else if (cellVertices.size() == 5)
			{
				pyras.resize(pyra_count + 1);
				// Insert vertices into vtkPoints vector
				for (int i = 0; i < 5; i++)
				{
					points->InsertNextPoint(cellVertices[i].getX(), cellVertices[i].getY(), cellVertices[i].getZ());
				}

				unstructuredGrids[poly_count] = vtkSmartPointer<vtkUnstructuredGrid>::New();
				unstructuredGrids[poly_count]->SetPoints(points);
				pyras[pyra_count] = vtkSmartPointer<vtkPyramid>::New();

				// Set points to the pyramid
				for (int i = 0; i < 4; i++)
				{
					pyras[pyra_count]->GetPointIds()->SetId(i, last_used_point_id + i);
				}
				last_used_point_id += 4;

				cellArray->InsertNextCell(pyras[pyra_count]);
				unstructuredGrids[poly_count]->SetCells(VTK_PYRAMID, cellArray);
				pyra_count++;

				// Hexahedron
			}
			else if (cellVertices.size() == 8)
			{

				hexas.resize(hexa_count + 1);

				// Insert vertices into vtkPoints vector
				for (int i = 0; i < 8; i++)
				{
					points->InsertNextPoint(cellVertices[i].getX(), cellVertices[i].getY(), cellVertices[i].getZ());
				}

				unstructuredGrids[poly_count] = vtkSmartPointer<vtkUnstructuredGrid>::New();
				// Maybe this needs to go after set points
				unstructuredGrids[poly_count]->SetPoints(points);
				hexas[hexa_count] = vtkSmartPointer<vtkHexahedron>::New();

				// Set points to the hexa
				for (int i = 0; i < 8; i++)
				{
					hexas[hexa_count]->GetPointIds()->SetId(i, last_used_point_id + 1 + i);
				}
				last_used_point_id += 4;

				cellArray->InsertNextCell(hexas[hexa_count]);
				unstructuredGrids[poly_count]->SetCells(VTK_HEXAHEDRON, cellArray);
				hexa_count++;
			}

			// Create mapper and set the current cell as its input
			mappers[poly_count] = vtkSmartPointer<vtkDataSetMapper>::New();
			mappers[poly_count]->SetInputData(unstructuredGrids[poly_count]);

			// Set mapper to actor
			actors[poly_count] = vtkSmartPointer<vtkActor>::New();
			actors[poly_count]->SetMapper(mappers[poly_count]);
			//actors[poly_count]->GetProperty()->SetColor(colors->GetColor3d("Cyan").GetData());

			// Get material of current cell
			Material mat1 = modCells[poly_count].getMaterial();

			// Get colour as hexadecimal string, convert it to separate r, g and b
			std::string matColour = mat1.getColour();
			const char *rgbColour = matColour.c_str();
			int r, g, b;
			sscanf(rgbColour, "%02x%02x%02x", &r, &g, &b);

			// Convert it to double and set it to range from 0 to 1
			double dr = (double)r / 255;
			double dg = (double)g / 255;
			double db = (double)b / 255;

			actors[poly_count]->GetProperty()->SetColor(dr, dg, db);

			actors[poly_count]->GetProperty()->SetSpecular(0.5);
			actors[poly_count]->GetProperty()->SetSpecularPower(5);
			// Add actor to renderer
			renderer->AddActor(actors[poly_count]);
			poly_count++;
		}

		modPolyData = vtkSmartPointer<vtkPolyData>::New();

		modPolyData->SetPolys(cellArray);
		modPolyData->SetPoints(points);

		// Use a triangle filter to obtain mass and surface area information
		vtkTriangleFilter *triangleFilter = vtkTriangleFilter::New();
		vtkMassProperties *massProperty = vtkMassProperties::New();
		triangleFilter->SetInputData(modPolyData);
		triangleFilter->Update();
		massProperty->SetInputConnection(triangleFilter->GetOutputPort());
		massProperty->Update();
		modSurfArea = massProperty->GetSurfaceArea();
		modVolume = massProperty->GetVolume();

		// Store all information in the stats strings
		surfAreaString = QString::number(modSurfArea) + " m^2";
		volumeString = QString::number(modVolume) + " m^3";
		cellString = QString::number(poly_count);
		pointString = QString::number(mod1.getVertexCount());

		emit statusUpdateMessage(QString("Loaded MOD model"), 0);
	}
	// Set flag back to true
	modelLoaded = true;

	// Enable buttons relating to model viewing
	setupButtons(modelLoaded);
	resetCamera();

	ui->qvtkWidget->GetRenderWindow()->Render();

	// Display the stats in the stats area
	ui->surfAreaValue->setText(surfAreaString);
	ui->volValue->setText(volumeString);
	ui->cellsValue->setText(cellString);
	ui->pointsValue->setText(pointString);
}

void MainWindow::clearModel()
{
	// Retain background colour
	double r, g, b;
	double r2, g2, b2;
	renderer->GetBackground(r, g, b);
	renderer->GetBackground2(r2, g2, b2);
	bool isGradient = renderer->GetGradientBackground();

	// Remove renderer from render window
	ui->qvtkWidget->GetRenderWindow()->RemoveRenderer(renderer);
	// Free previous renderer by assigning it to a NULL pointer
	renderer = NULL;
	// Create a new pointer to a renderer
	renderer = vtkSmartPointer<vtkRenderer>::New();
	// Add the renderer back
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
	ui->qvtkWidget->GetRenderWindow()->Render();

	// Set previous background colour
	renderer->SetBackground(r, g, b);
	renderer->SetBackground2(r2, g2, b2);

	if (isGradient)
	{
		renderer->GradientBackgroundOn();
	}

	// Clear stats text
	ui->surfAreaValue->setText("");
	ui->volValue->setText("");
	ui->cellsValue->setText("");
	ui->pointsValue->setText("");

	// Disable STL only filters
	ui->shrinkButton->setEnabled(false);
	ui->resetFiltersButton->setEnabled(false);
	ui->clipButton->setEnabled(false);

	modelLoaded = false;
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::resetCamera()
{
	// These lines are needed to ensure the button can be pressed more than
	// once per each model
	renderer->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
	renderer->GetActiveCamera()->SetViewUp(0.201282, 0.526811, -0.299848);
	renderer->GetActiveCamera()->SetPosition(0.795337, -0.696117, -0.689135);

	// Reset camera and re-render scene
	renderer->ResetCamera();
}

void MainWindow::handleActionOpen()
{
	// Prompt user for a filename
	inputFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
												 QDir::currentPath(),
												 tr("Supported Models (*.mod, *.stl);;STL Model (*.stl);;Proprietary Model (*.mod)"));

	if (!inputFileName.isEmpty() && !inputFileName.isNull())
	{
		if (modelLoaded)
		{
			clearModel();
		}
		loadModel(inputFileName);
	}
	else
	{
		emit statusUpdateMessage(QString("Error while opening file"), 0);
	}
}

void MainWindow::handleActionSave()
{
	// Only save if a model is already loaded
	if (!modelLoaded)
	{
		emit statusUpdateMessage(QString("Error: cannot save when a model is not loaded"), 0);
	}
	else
	{
		// Prompt user for a filename
		QString outputFileName = QFileDialog::getSaveFileName(this, tr("Save File"),
															  QDir::currentPath(),
															  tr("Supported Models (*.mod *.stl);;STL Model (*.stl);;Proprietary Model (*.mod)"));

		if (!outputFileName.isEmpty() && !outputFileName.isNull())
		{
			if (!QFile::copy(inputFileName, outputFileName))
			{
				emit statusUpdateMessage(QString("Error while saving file"), 0);
			}
		}
		else
		{
			emit statusUpdateMessage(QString("Error: no save name inserted"), 0);
		}
	}
}

void MainWindow::handleActionClose()
{
	if (modelLoaded)
	{
		clearModel();
	}
	// Reset buttons to initial state (some buttons greyed out)
	setupButtons(modelLoaded);
	emit statusUpdateMessage(QString("File closed"), 0);
}

void MainWindow::handleActionStlTest()
{
	inputFileName = "tests/ExampleSTL.stl";
	if (modelLoaded)
	{
		clearModel();
	}
	loadModel(inputFileName);
	//emit statusUpdateMessage(QString("Loaded test STL model"), 0);
}

void MainWindow::handleActionModTest()
{
	inputFileName = "tests/ExampleModel.mod";
	if (modelLoaded)
	{
		clearModel();
	}
	loadModel(inputFileName);
	//emit statusUpdateMessage(QString("Loaded test MOD model"), 0);
}

void MainWindow::handleActionPrint()
{
	// Prompt the user for filename
	QString screenshotName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Images (*.png)"));
	// Only export if a filename has been entered
	if (!screenshotName.isEmpty() && !screenshotName.isNull())
	{
		// Enable usage of alpha channel
		renderWindow->SetAlphaBitPlanes(1);
		ui->qvtkWidget->GetRenderWindow()->Render();
		vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
		windowToImageFilter->SetInput(renderWindow);

		// Record the alpha (transparency channel)
		windowToImageFilter->SetInputBufferTypeToRGBA();
		windowToImageFilter->ReadFrontBufferOff(); // read from the back buffer
		windowToImageFilter->Update();

		screenshotName += ".png";

		// Convert QString
		vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
		std::string stdName = screenshotName.toStdString();
		const char *charName = stdName.c_str();

		// Write PNG
		writer->SetFileName(charName);
		writer->SetInputConnection(windowToImageFilter->GetOutputPort());
		writer->Write();

		emit statusUpdateMessage(QString("Screenshot saved successfully"), 0);
	}
}

void MainWindow::handleActionFullScreen()
{
	if (this->isFullScreen())
	{
		this->showNormal();
	}
	else
	{
		this->showFullScreen();
	}
}

void MainWindow::handleActionAbout()
{
	HelpDialog *helpWindow = new HelpDialog();
	helpWindow->show();
}

void MainWindow::handleActionExportData()
{
	// Prompt user for a filename
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
													QDir::currentPath(),
													tr("Text file (*.txt)"));

	// Only export if a filename has been entered
	if (!fileName.isEmpty() && !fileName.isNull())
	{
		fileName += ".txt";

		// Open the file
		QFile outFile(fileName);
		outFile.open(QIODevice::WriteOnly);

		// Print an error if file fails to open
		if (!outFile.isOpen())
		{
			QMessageBox messageBox;
			messageBox.critical(0, "Error", "Error while writing to the file");
			messageBox.setFixedSize(500, 200);
		}

		// Initialise output string
		QString outStr = "";

		outStr += "Volume: ";
		outStr += volumeString;
		outStr += "\n";

		outStr += "Surface area: ";
		outStr += surfAreaString;
		outStr += "\n";

		outStr += "Cells: ";
		outStr += cellString;
		outStr += "\n";

		outStr += "Points: ";
		outStr += pointString;
		outStr += "\n";

		// Initialise outStream
		QTextStream outStream(&outFile);

		// Write to stream
		outStream << outStr;

		// Close file
		outFile.close();

		emit statusUpdateMessage(QString("Data exported successfully"), 0);
	}
}

void MainWindow::handleActionResetFilters()
{
	ui->resetFiltersButton->click();
}

void MainWindow::handleActionResetCamera()
{
	ui->resetCameraButton->click();
}

void MainWindow::handleActionResetProperties()
{
	ui->resetPropertiesButton->click();
}

void MainWindow::handleActionResetLighting()
{
	ui->resetLightingButton->click();
}

void MainWindow::on_shrinkButton_clicked()
{
	// Prompt user for shrink factor
	bool success;
	double shrinkFactor = QInputDialog::getDouble(this, tr("Input dialog"),
												  tr("Insert shrink factor (0 to 1)"), 0.5,
												  0, 1, 2, &success);
	if (success)
	{
		// Connect shrink filter to STL reader
		vtkSmartPointer<vtkShrinkFilter> shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
		shrinkFilter->SetInputConnection(reader->GetOutputPort());
		shrinkFilter->SetShrinkFactor(shrinkFactor);
		shrinkFilter->Update();
		mappers[0]->SetInputConnection(shrinkFilter->GetOutputPort());

		actors[0]->SetMapper(mappers[0]);

		ui->qvtkWidget->GetRenderWindow()->Render();
		ui->shrinkButton->setCheckable(true);
		emit statusUpdateMessage(QString("Shrink filter enabled"), 0);
	}
	else
	{
		emit statusUpdateMessage(QString("Error while enabling shrink filter"), 0);
	}
	ui->shrinkButton->setCheckable(true);
	ui->shrinkButton->setChecked(true);
}

void MainWindow::on_clipDialog_dialogAccepted()
{
	clipWindowShown = false;
}

void MainWindow::on_clipDialog_dialogRejected()
{
	// Set clip plane parameters to how they were before the dialog was opened
	clipX = prevClipX;
	clipY = prevClipY;
	clipZ = prevClipZ;
	clipNormalX = prevClipNormalX;
	clipNormalY = prevClipNormalY;
	clipNormalZ = prevClipNormalZ;

	clipPlane->SetOrigin(clipX, clipY, clipZ);

	clipWindowShown = false;
	ui->qvtkWidget->GetRenderWindow()->Render();
	emit statusUpdateMessage(QString("Changes to clip filter cancelled"), 0);
}

void MainWindow::on_clipButton_clicked()
{

	// Toggle clip dialog between shown and hidden depending on its current state
	if (clipWindowShown)
	{
		clipWindow->close();
		clipWindowShown = false;
	}
	else
	{
		clipWindow->show();
		clipWindowShown = true;

		// Store current plane parameters in case dialog is rejected
		// (cancel button is pressed)
		prevClipX = clipX;
		prevClipY = clipY;
		prevClipZ = clipZ;
		prevClipNormalX = clipNormalX;
		prevClipNormalY = clipNormalY;
		prevClipNormalZ = clipNormalZ;

		// When clicked for the first time, initialise clip plane with these parameters
		if (!clipFilterEnabled)
			clipFilter = NULL;
		clipPlane = NULL;
		// Connect clip filter to STL reader
		clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
		clipPlane = vtkSmartPointer<vtkPlane>::New();
		clipFilter->SetInputConnection(reader->GetOutputPort());
		clipPlane->SetOrigin(0.0, 0.0, 0.0);
		clipPlane->SetNormal(-1.0, 0.0, 0.0);
		clipFilter->SetClipFunction(clipPlane.Get());
		mappers[0]->SetInputConnection(clipFilter->GetOutputPort());
		actors[0]->SetMapper(mappers[0]);

		ui->qvtkWidget->GetRenderWindow()->Render();
		ui->clipButton->setCheckable(true);
		ui->clipButton->setChecked(true);
		emit statusUpdateMessage(QString("Clip filter enabled"), 0);
		clipFilterEnabled = true;
	}
	ui->clipButton->setCheckable(true);
	ui->clipButton->setChecked(true);
}

void MainWindow::on_clipXSlider_sliderMoved(int position)
{
	if (position == 99)
	{
		clipX = 10;
	}
	else
	{
		clipX = -(float)position * 10;
	}
	clipPlane->SetOrigin(clipX, clipY, clipZ);
	clipFilter->SetClipFunction(clipPlane.Get());
	mappers[0]->SetInputConnection(clipFilter->GetOutputPort());
	actors[0]->SetMapper(mappers[0]);
	ui->qvtkWidget->GetRenderWindow()->Render();
	emit statusUpdateMessage(QString("X parameter of clip filter changed"), 0);
}

void MainWindow::on_clipYSlider_sliderMoved(int position)
{
	if (position == 99)
	{
		clipY = 20;
	}
	else
	{
		clipY = (float)position * 20;
	}
	clipPlane->SetOrigin(clipX, clipY, clipZ);
	clipFilter->SetClipFunction(clipPlane.Get());
	mappers[0]->SetInputConnection(clipFilter->GetOutputPort());
	actors[0]->SetMapper(mappers[0]);
	ui->qvtkWidget->GetRenderWindow()->Render();
	emit statusUpdateMessage(QString("Y parameter of clip filter changed"), 0);
}

void MainWindow::on_clipZSlider_sliderMoved(int position)
{
	if (position == 99)
	{
		clipZ = 20;
	}
	else
	{
		clipZ = (float)position * 20;
	}
	clipPlane->SetOrigin(clipX, clipY, clipZ);
	clipFilter->SetClipFunction(clipPlane.Get());
	mappers[0]->SetInputConnection(clipFilter->GetOutputPort());
	actors[0]->SetMapper(mappers[0]);
	ui->qvtkWidget->GetRenderWindow()->Render();
	emit statusUpdateMessage(QString("Z parameter of clip filter changed"), 0);
}

void MainWindow::on_clipXDial_sliderMoved(int position)
{
	if (position == 99)
	{
		clipNormalX = 10;
	}
	else
	{
		clipNormalX = (float)position * 10;
	}
	clipPlane->SetNormal(clipNormalX, clipNormalY, clipNormalZ);
	clipFilter->SetClipFunction(clipPlane.Get());
	mappers[0]->SetInputConnection(clipFilter->GetOutputPort());
	actors[0]->SetMapper(mappers[0]);
	ui->qvtkWidget->GetRenderWindow()->Render();
	emit statusUpdateMessage(QString("X rotation of clip filter changed"), 0);
}

void MainWindow::on_clipYDial_sliderMoved(int position)
{
	if (position == 99)
	{
		clipNormalY = 10;
	}
	else
	{
		clipNormalY = (float)position * 10;
	}
	clipPlane->SetNormal(clipNormalX, clipNormalY, clipNormalZ);
	clipFilter->SetClipFunction(clipPlane.Get());
	mappers[0]->SetInputConnection(clipFilter->GetOutputPort());
	actors[0]->SetMapper(mappers[0]);
	ui->qvtkWidget->GetRenderWindow()->Render();
	emit statusUpdateMessage(QString("Y rotation of clip filter changed"), 0);
}

void MainWindow::on_clipZDial_sliderMoved(int position)
{
	if (position == 99)
	{
		clipNormalZ = 10;
	}
	else
	{
		clipNormalZ = (float)position * 10;
	}
	clipPlane->SetNormal(clipNormalX, clipNormalY, clipNormalZ);
	clipFilter->SetClipFunction(clipPlane.Get());
	mappers[0]->SetInputConnection(clipFilter->GetOutputPort());
	actors[0]->SetMapper(mappers[0]);
	ui->qvtkWidget->GetRenderWindow()->Render();
	emit statusUpdateMessage(QString("Z rotation of clip filter changed"), 0);
}

void MainWindow::on_bkgColourButton_clicked()
{
	// Prompt user for colour
	QColor rgbColours = QColorDialog::getColor(Qt::white, this, "Choose Background Colour");
	double r = rgbColours.redF();
	double g = rgbColours.greenF();
	double b = rgbColours.blueF();

	// Check that colour is valid, otherwise show an error
	if (rgbColours.isValid())
	{
		renderer->SetBackground(r, g, b);
		ui->qvtkWidget->GetRenderWindow()->Render();
	}
	else
	{
		emit statusUpdateMessage(QString("Errour while changing background colour"), 0);
	}
	emit statusUpdateMessage(QString("Background colour changed"), 0);
}

void MainWindow::on_modColourButton_clicked()
{
	// Prompt user for colour
	QColor rgbColours = QColorDialog::getColor(Qt::white, this, "Choose Model Colour");
	double r = rgbColours.redF();
	double g = rgbColours.greenF();
	double b = rgbColours.blueF();

	// Check that colour is valid, otherwise show an error
	if (rgbColours.isValid())
	{

		// Ensure all actors are properly coloured in case it's a .mod file
		for (int i = 0; i < actors.size(); i++)
		{
			actors[i]->GetProperty()->SetColor(r, g, b);
		}
		ui->qvtkWidget->GetRenderWindow()->Render();
	}
	else
	{
		emit statusUpdateMessage(QString("Error while changing model colour"), 0);
	}
	emit statusUpdateMessage(QString("Model colour changed"), 0);
}

void MainWindow::on_resetCameraButton_clicked()
{
	resetCamera();
	ui->qvtkWidget->GetRenderWindow()->Render();
	emit statusUpdateMessage(QString("Camera has been reset"), 0);
}

void MainWindow::on_resetPropertiesButton_clicked()
{
	if (modelLoaded)
	{
		clearModel();
	}

	// Recolor model
	loadModel(inputFileName);

	// Set default background colour
	renderer->GradientBackgroundOn();
	renderer->SetBackground(colors->GetColor3d("Black").GetData());
	renderer->SetBackground2(0, 0.6, 0.5);

	emit statusUpdateMessage(QString("Properties have been reset"), 0);
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_resetLightingButton_clicked()
{
	// Set maximum opacity
	ui->opacitySlider->setValue(99);
	for (int i = 0; i < actors.size(); i++)
	{
		actors[i]->GetProperty()->SetOpacity(1);
	}

	// Remove external light
	ui->intensityCheckBox->setChecked(false);
	renderer->RemoveAllLights();
	ui->intensitySlider->setValue(49);
	ui->intensitySlider->setEnabled(false);

	// Set specularity to half value
	ui->specularitySlider->setValue(49);
	for (int i = 0; i < actors.size(); i++)
	{
		actors[i]->GetProperty()->SetSpecular(0.5);
	}

	emit statusUpdateMessage(QString("Lighting has been reset"), 0);
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_resetFiltersButton_clicked()
{
	if (modelLoaded)
	{
		clearModel();
	}

	// Recolor model
	loadModel(inputFileName);

	// Uncheck buttons
	ui->shrinkButton->setChecked(false);
	ui->clipButton->setChecked(false);

	clipFilterEnabled = false;

	clipWindow->hide();

	clipX = 0;
	clipY = 0;
	clipZ = 0;
	clipNormalX = -1;
	clipNormalY = 0;
	clipNormalZ = 0;

	emit statusUpdateMessage(QString("Filters have been reset"), 0);
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_posXButton_clicked()
{
	renderer->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
	renderer->GetActiveCamera()->SetViewUp(0, 0, 0);
	renderer->GetActiveCamera()->SetPosition(1, 0, 0);

	// Re-render scene
	renderer->ResetCamera();
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_posYButton_clicked()
{
	renderer->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
	renderer->GetActiveCamera()->SetViewUp(1, 0, 0);
	renderer->GetActiveCamera()->SetPosition(0, 1, 0);

	// Re-render scene
	renderer->ResetCamera();
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_posZButton_clicked()
{
	renderer->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
	renderer->GetActiveCamera()->SetViewUp(0, 1, 0);
	renderer->GetActiveCamera()->SetPosition(0, 0, 1);

	// Re-render scene
	renderer->ResetCamera();
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_pos90Button_clicked()
{
	renderer->GetActiveCamera()->Roll(-90);

	// Re-render scene
	renderer->ResetCamera();
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_negXButton_clicked()
{
	renderer->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
	renderer->GetActiveCamera()->SetViewUp(0, 1, 0);
	renderer->GetActiveCamera()->SetPosition(-1, 0, 0);

	// Re-render scene
	renderer->ResetCamera();
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_negYButton_clicked()
{
	renderer->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
	renderer->GetActiveCamera()->SetViewUp(1, 0, 0);
	renderer->GetActiveCamera()->SetPosition(0, -1, 0);

	// Re-render scene
	renderer->ResetCamera();
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_negZButton_clicked()
{
	renderer->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
	renderer->GetActiveCamera()->SetViewUp(0, 1, 0);
	renderer->GetActiveCamera()->SetPosition(0, 0, -1);

	// Re-render scene
	renderer->ResetCamera();
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_neg90Button_clicked()
{
	renderer->GetActiveCamera()->Roll(90);

	// Re-render scene
	renderer->ResetCamera();
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::handleActionEnableIntensity()
{
	Qt::CheckState state = ui->intensityCheckBox->checkState();
	if (state == Qt::Unchecked)
	{
		ui->intensityCheckBox->setCheckState(Qt::Checked);
	}
	else if (state == Qt::Checked)
	{
		ui->intensityCheckBox->setCheckState(Qt::Unchecked);
	}
}

void MainWindow::handleActionShowAxes()
{
	Qt::CheckState state = ui->showAxesCheckBox->checkState();
	if (state == Qt::Unchecked)
	{
		ui->showAxesCheckBox->setCheckState(Qt::Checked);
	}
	else if (state == Qt::Checked)
	{
		ui->showAxesCheckBox->setCheckState(Qt::Unchecked);
	}
}

void MainWindow::on_gradientCheckBox_stateChanged(int state)
{
	// Note: state == 1 means partially checked
	if (state == 0) // unchecked
	{
		renderer->GradientBackgroundOff();
		emit statusUpdateMessage(QString("Gradient background disabled"), 0);
	}
	else if (state == 2) // checked
	{
		double r, g, b;
		renderer->GetBackground(r, g, b);
		renderer->GradientBackgroundOn();
		renderer->SetBackground(r, g, b);
		renderer->SetBackground2(0, 0.6, 0.5);
		emit statusUpdateMessage(QString("Gradient background enabled"), 0);
	}
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_intensityCheckBox_stateChanged(int state)
{
	// Note: state == 1 means partially checked
	if (state == 0) // unchecked
	{
		ui->intensitySlider->setEnabled(false);
		renderer->RemoveAllLights();
		emit statusUpdateMessage(QString("External light disabled"), 0);
	}
	else if (state == 2) // checked
	{
		renderer->AddLight(light);
		ui->intensitySlider->setEnabled(true);
		emit statusUpdateMessage(QString("External light enabled"), 0);
	}
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_showAxesCheckBox_stateChanged(int state)
{
	// Note: state == 1 means partially checked
	if (state == 0) // unchecked
	{
		renderer->RemoveActor(axes);
		emit statusUpdateMessage(QString("Coordinate axes disabled"), 0);
	}
	else if (state == 2) // checked
	{
		renderer->AddActor(axes);
		emit statusUpdateMessage(QString("Coordinate axes enabled"), 0);
	}
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_wireframeRadio_toggled(bool checked)
{
	if (checked)
	{
		for (int i = 0; i < actors.size(); i++)
		{
			actors[i]->GetProperty()->SetRepresentationToWireframe();
		}
	}
	emit statusUpdateMessage(QString("Wireframe visualization enabled"), 0);
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_pointsRadio_toggled(bool checked)
{
	if (checked)
	{
		for (int i = 0; i < actors.size(); i++)
		{
			actors[i]->GetProperty()->SetRepresentationToPoints();
		}
	}
	emit statusUpdateMessage(QString("Points visualization enabled"), 0);
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_surfaceRadio_toggled(bool checked)
{
	if (checked)
	{
		for (int i = 0; i < actors.size(); i++)
		{
			actors[i]->GetProperty()->SetRepresentationToSurface();
		}
	}
	emit statusUpdateMessage(QString("Surface visualization enabled"), 0);
	ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_opacitySlider_sliderMoved(int position)
{
	float pos;
	if (position == 99)
	{
		pos = 1;
	}
	else
	{
		pos = (float)position / 100;
	}

	if (actors.size() == 1)
	{
		actors[0]->GetProperty()->SetOpacity(pos);
		ui->qvtkWidget->GetRenderWindow()->Render();
	}
}

void MainWindow::on_opacitySlider_valueChanged(int value)
{
	float pos;
	if (value == 99)
	{
		pos = 1;
	}
	else
	{
		pos = (float)value / 100;
	}

	if (actors.size() != 1)
	{
		// Ensure all actors are properly coloured in case it's a .mod file
		for (int i = 0; i < actors.size(); i++)
		{
			actors[i]->GetProperty()->SetOpacity(pos);
		}
		ui->qvtkWidget->GetRenderWindow()->Render();
	}
}

void MainWindow::on_specularitySlider_sliderMoved(int position)
{
	float pos;
	if (position == 99)
	{
		pos = 1;
	}
	else
	{
		pos = (float)position / 100;
	}

	if (actors.size() == 1)
	{
		actors[0]->GetProperty()->SetSpecular(pos);

		ui->qvtkWidget->GetRenderWindow()->Render();
	}
}

void MainWindow::on_specularitySlider_valueChanged(int value)
{
	float pos;
	if (value == 99)
	{
		pos = 1;
	}
	else
	{
		pos = (float)value / 100;
	}

	if (actors.size() != 1)
	{
		// Ensure all actors are properly coloured in case it's a .mod file
		for (int i = 0; i < actors.size(); i++)
		{
			actors[i]->GetProperty()->SetSpecular(pos);
		}
		ui->qvtkWidget->GetRenderWindow()->Render();
	}
}

void MainWindow::on_intensitySlider_sliderMoved(int position)
{
	float pos;
	if (position == 99)
	{
		pos = 1;
	}
	else
	{
		pos = (float)position / 100;
	}

	light->SetIntensity(pos);
	ui->qvtkWidget->GetRenderWindow()->Render();
}