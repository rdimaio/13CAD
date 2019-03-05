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

#include <vtkCellArray.h>
#include <vtkCellType.h>
#include <vtkPoints.h>

#include <vtkUnstructuredGrid.h>
#include <vtkPyramid.h>
#include <vtkTetra.h>

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
  	Model mod1(inputFilename);

	// Now need to create a VTK render window and link it to the QtVTK widget
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	ui->qvtkWidget->SetRenderWindow( renderWindow );			// note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt creator

	vtkSmartPointer<vtkActor> actor;

	if (mod1.getIsSTL()) {
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
		// ONLY ONE ACTOR, ONE MAPPER, AND ONE READER.
		// 1. MAKE UNSTRUCTURED GRID
		// 2. PUT POINTS IN IT
		// 3. MAKE CELL, PUT IT IN ARRAY
		// 4. LOOP OVER
		// 5. AT THE END, MAKE ACTOR

		// Get vector of cells from the model
		std::vector<Cell> modCells = mod1.getCells();
		// Iterate over cells
		for(std::vector<Cell>::iterator it = modCells.begin(); it != modCells.begin(); ++it) {
			std::vector<Vector3D> cellVertices = it->getVertices();
			vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
			// Pyramid
			if (cellVertices.size() == 5) {
				double p0[3] = {cellVertices[0].getX(), cellVertices[0].getY(), cellVertices[0].getZ()};
  				double p1[3] = {cellVertices[1].getX(), cellVertices[1].getY(), cellVertices[1].getZ()};
  				double p2[3] = {cellVertices[2].getX(), cellVertices[2].getY(), cellVertices[2].getZ()};
  				double p3[3] = {cellVertices[3].getX(), cellVertices[3].getY(), cellVertices[3].getZ()};
  				double p4[3] = {cellVertices[4].getX(), cellVertices[4].getY(), cellVertices[4].getZ()};

  				points->InsertNextPoint(p0);
  				points->InsertNextPoint(p1);
  				points->InsertNextPoint(p2);
  				points->InsertNextPoint(p3);
  				points->InsertNextPoint(p4);

  				vtkSmartPointer<vtkPyramid> pyramid = vtkSmartPointer<vtkPyramid>::New();
  				pyramid->GetPointIds()->SetId(0,0);
  				pyramid->GetPointIds()->SetId(1,1);
  				pyramid->GetPointIds()->SetId(2,2);
  				pyramid->GetPointIds()->SetId(3,3);
  				pyramid->GetPointIds()->SetId(4,4);

  				

  				vtkSmartPointer<vtkUnstructuredGrid> ug = 
  				    vtkSmartPointer<vtkUnstructuredGrid>::New();
  				ug->SetPoints(points);
  				ug->InsertNextCell(pyramid->GetCellType(),pyramid->GetPointIds());
2
  				//Create an actor and mapper
  				vtkSmartPointer<vtkNamedColors> colors =
  				  vtkSmartPointer<vtkNamedColors>::New();
  				vtkSmartPointer<vtkDataSetMapper> mapper = 
  				    vtkSmartPointer<vtkDataSetMapper>::New();
  				mapper->SetInputData(ug);
				//vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  				actor->SetMapper(mapper);
			} else if (cellVertices.size() == 4) { // Tetrahedron 
				points->InsertNextPoint(0, 0, 0);
  				points->InsertNextPoint(1, 0, 0);
  				points->InsertNextPoint(1, 1, 0);
				points->InsertNextPoint(1, 1, 0);


			} else if (cellVertices.size() == 8) { // Hexahedron
			
			}
		int i = 0;
		if (i = 0) { 
		break; 
		}	
		}
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
	
	
	ui->sa->setIcon(QIcon("ModelLoader/src/gui/Icons/filesave.png")); //choose the icon location

	// Render and interact
	//renderWindow->Render();					// ###### Not needed with Qt ######
	//renderWindowInteractor->Start();			// ###### Not needed with Qt ######

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_sa_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png)")); 
        QScreen *screen = QGuiApplication::primaryScreen();
        screen->grabWindow(ui->qvtkWidget->winId()).save(filename);

}

