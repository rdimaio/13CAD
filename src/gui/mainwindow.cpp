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
#include <vtkHexahedron.h>

// STL reading libraries
#include <vtkSTLReader.h>
#include <vtkPolyDataMapper.h>

// Qt headers
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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

	// Create a renderer, and render window
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
	//vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();		// ###### We've already created the renderWindow this time ######
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);									// ###### ask the QtVTKOpenGLWidget for its renderWindow ######

	vtkSmartPointer<vtkCellArray> cellArray = vtkSmartPointer<vtkCellArray>::New();

	std::vector<vtkSmartPointer<vtkUnstructuredGrid>> unstructuredGrids;
  	std::vector<vtkSmartPointer<vtkTetra>> tetras;
	std::vector<vtkSmartPointer<vtkHexahedron>> hexas;
  	std::vector<vtkSmartPointer<vtkDataSetMapper>> mappers;
  	std::vector<vtkSmartPointer<vtkActor>> actors;
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

	qInfo() << "Window successfully initialised"; // debug

	if (mod1.getIsSTL()) {
	
	qInfo() << "Model is STL"; // debug
  	
	// Visualize
	actors.resize(1);
	mappers.resize(1);
	vtkSmartPointer<vtkSTLReader> reader =
	vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName(inputFilename.c_str());
	reader->Update();

	// WARNING: CHANGED POLYDATASET TO DATASET HERE, IT COULD BREAK
  	mappers[0] = vtkSmartPointer<vtkDataSetMapper>::New();
  	mappers[0]->SetInputConnection(reader->GetOutputPort());

	// Create an actor that is used to set the cube's properties for rendering and place it in the window
	actors[0] = vtkSmartPointer<vtkActor>::New();
	actors[0]->SetMapper(mappers[0]);

	} else {

		qInfo() << "Model is of .mod format"; // debug

		int poly_count = 0;
		int tetra_count = 0; // Number of tetras
		int hexa_count = 0;
		int last_used_point_id = 0; // ID of last point used
		// Get vector of cells from the model
		std::vector<Cell> modCells = mod1.getCells();

		// Resize to new model
		unstructuredGrids.resize(modCells.size());
    	actors.resize(modCells.size());
    	mappers.resize(modCells.size());

		// For each cell
		for(std::vector<Cell>::iterator it = modCells.begin(); it != modCells.end(); ++it) {

			// Get vertices of the cell
			std::vector<Vector3D> cellVertices = it->getVertices();

			// qInfo() << "x:";
			// qInfo() << cellVertices[0].getX(); // debug
 
			// qInfo() << "y:";
			// qInfo() << cellVertices[0].getY(); // debug
 
			// qInfo() << "z:";
			// qInfo() << cellVertices[0].getZ(); // debug

			// Pyramid
			if (cellVertices.size() == 5) {

			} else if (cellVertices.size() == 4) { // Tetrahedron
				tetras.resize(tetra_count+1); 
				qInfo() << "tetra"; // debug
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
					tetras[tetra_count]->GetPointIds()->SetId(i, last_used_point_id+i);
				}
				last_used_point_id += 4;

				cellArray->InsertNextCell(tetras[tetra_count]);
    			unstructuredGrids[poly_count]->SetCells(VTK_TETRA, cellArray);

				mappers[poly_count] = vtkSmartPointer<vtkDataSetMapper>::New();
				mappers[poly_count]->SetInputData(unstructuredGrids[poly_count]);

				actors[poly_count] = vtkSmartPointer<vtkActor>::New();
				actors[poly_count]->SetMapper(mappers[poly_count]);
				actors[poly_count]->GetProperty()->SetColor(colors->GetColor3d("Cyan").GetData());
				renderer->AddActor(actors[poly_count]);

				// actors[poly_count]->GetProperty()->SetColor( colors->GetColor3d("Red").GetData());

				tetra_count++;
				poly_count++;
			// Hexahedron
			} else if (cellVertices.size() == 8) {

				hexas.resize(hexa_count+1);

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
					hexas[hexa_count]->GetPointIds()->SetId(i, last_used_point_id+1+i);
				}
				last_used_point_id += 4;

				cellArray->InsertNextCell(hexas[hexa_count]);
				unstructuredGrids[poly_count]->SetCells(VTK_HEXAHEDRON, cellArray);

				mappers[poly_count] = vtkSmartPointer<vtkDataSetMapper>::New();
				mappers[poly_count]->SetInputData(unstructuredGrids[poly_count]);
				actors[poly_count] = vtkSmartPointer<vtkActor>::New();
				actors[poly_count]->SetMapper(mappers[poly_count]);
				actors[poly_count]->GetProperty()->SetColor(colors->GetColor3d("Cyan").GetData());
				renderer->AddActor(actors[poly_count]);
				// actors[poly_count]->GetProperty()->SetColor( colors->GetColor3d("Red").GetData());
				hexa_count++;
				poly_count++;

			}
		}
		qInfo() << tetra_count; // debug
		qInfo() << hexa_count; // debug
		qInfo() << poly_count; // debug
		qInfo() << last_used_point_id; // debug
	}

	//actor->GetProperty()->EdgeVisibilityOn();


	// Link a renderWindowInteractor to the renderer (this allows you to capture mouse movements etc)  ###### Not needed with Qt ######
	//vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	//renderWindowInteractor->SetRenderWindow( ui->vtkWidget->GetRenderWindow() );				
	renderer->SetBackground( colors->GetColor3d("Green").GetData() );

	// Setup the renderers's camera
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Azimuth(30);
	renderer->GetActiveCamera()->Elevation(30);
	renderer->ResetCameraClippingRange();

	// Render and interact
	// renderWindow->Render();					// ###### Not needed with Qt ######
	// renderWindowInteractor->Start();			// ###### Not needed with Qt ######
	qInfo() << "Window complete"; // debug
}

MainWindow::~MainWindow()
{
    delete ui;
}
