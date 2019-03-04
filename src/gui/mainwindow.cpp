// VTK libraries
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
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
#include <vtkGenericOpenGLRenderWindow.h>

// STL reading libraries
#include <vtkSTLReader.h>
#include <vtkPolyDataMapper.h>

// Qt headers
#include "mainwindow.h"
#include "ui_mainwindow.h"

// Local headers
#include "model.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // standard call to setup Qt UI (same as previously)
    ui->setupUi( this );
	
	//std::string inputFilename = "src/gui/test.stl";
	std::string inputFilename = "tests/ExampleModel.mod";
	// Load model
  	Model model(inputFilename);

	// Now need to create a VTK render window and link it to the QtVTK widget
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	ui->qvtkWidget->SetRenderWindow( renderWindow );			// note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt creator

	vtkSmartPointer<vtkActor> actor;

	if (model.getIsSTL()) {
  	// Visualize
	vtkSmartPointer<vtkSTLReader> reader =
	vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName(inputFilename.c_str());
	reader->Update();

  	vtkSmartPointer<vtkPolyDataMapper> mapper =
  	  vtkSmartPointer<vtkPolyDataMapper>::New();
  	mapper->SetInputConnection(reader->GetOutputPort());

	// Create an actor that is used to set the cube's properties for rendering and place it in the window
	actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	} else {
		// Now use the VTK libraries to render something. To start with you can copy-paste the cube example code, there are comments to show where the code must be modified.
		//--------------------------------------------- Code From Example 1 --------------------------------------------------------------------------
		// Create a cube using a vtkCubeSource
		vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();

		// Create a mapper that will hold the cube's geometry in a format suitable for rendering
		vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
		mapper->SetInputConnection( cubeSource->GetOutputPort() );

		// Create an actor that is used to set the cube's properties for rendering and place it in the window
		actor = vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);
	}

	//actor->GetProperty()->EdgeVisibilityOn();

	vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
	actor->GetProperty()->SetColor( colors->GetColor3d("Red").GetData() );

	// Create a renderer, and render window
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	//vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();		// ###### We've already created the renderWindow this time ######
	ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );									// ###### ask the QtVTKOpenGLWidget for its renderWindow ######

	// Link a renderWindowInteractor to the renderer (this allows you to capture mouse movements etc)  ###### Not needed with Qt ######
	//vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	//renderWindowInteractor->SetRenderWindow( ui->vtkWidget->GetRenderWindow() );				

	// Add the actor to the scene
	renderer->AddActor(actor);
	renderer->SetBackground( colors->GetColor3d("Silver").GetData() );

	// Setup the renderers's camera
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Azimuth(30);
	renderer->GetActiveCamera()->Elevation(30);
	renderer->ResetCameraClippingRange();

	// Render and interact
	//renderWindow->Render();					// ###### Not needed with Qt ######
	//renderWindowInteractor->Start();			// ###### Not needed with Qt ######

}

MainWindow::~MainWindow()
{
    delete ui;
}
