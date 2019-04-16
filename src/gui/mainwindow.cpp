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
#include <vtkGenericOpenGLRenderWindow.h>

// VTK libraries - cells
#include <vtkCellArray.h>
#include <vtkCellType.h>
#include <vtkPoints.h>
#include <vtkUnstructuredGrid.h>
#include <vtkTetra.h>
#include <vtkPyramid.h>
#include <vtkHexahedron.h>

// VTK libraries - STL reading
#include <vtkSTLReader.h>
#include <vtkPolyDataMapper.h>

// Qt headers
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

// Local headers
#include "model.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // standard call to setup Qt UI (same as previously)
    ui->setupUi(this);

    connect( ui->modelButton, SIGNAL(clicked()), this, SLOT(handleModelButton()) );
    connect( ui->backgButton, SIGNAL(clicked()), this, SLOT(handleBackgButton()) );

	// Load model
	// (maybe only do model mod1 in case it's a .mod file, remove isstl from model,
	// and check here, so that you don't construct a model in case it's stl.)
  	Model mod1(inputFilename);

	// Create a VTK render window and link it to the QtVTK widget
	// (vtkWidget is the name gave to QtVTKOpenGLWidget in Qt Creator)
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	ui->qvtkWidget->SetRenderWindow(renderWindow);

	// Create a renderer and add it to the render window
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

	// Create colors
	vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

	// Create cell array to store the cells of the .mod file
	vtkSmartPointer<vtkCellArray> cellArray = vtkSmartPointer<vtkCellArray>::New();

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
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

	qInfo() << "Window successfully initialised"; // debug

	if (mod1.getIsSTL()) {

	qInfo() << "Model is STL"; // debug

	actors.resize(1);
	mappers.resize(1);

	// Visualize
	vtkSmartPointer<vtkSTLReader> reader =
	vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName(inputFilename.c_str());
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
	renderer->AddActor(actors[0]);

	} else {

		qInfo() << "Model is of .mod format"; // debug

		int poly_count = 0;
		int tetra_count = 0; // Number of tetrahedrons
		int pyra_count = 0; // Number of pyramids
		int hexa_count = 0; // Number of hexahedrons
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

			// Tetrahedron
			if (cellVertices.size() == 4) {
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
			
			// Pyramid
			} else if (cellVertices.size() == 5) {
				pyras.resize(pyra_count+1); 
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
					pyras[pyra_count]->GetPointIds()->SetId(i, last_used_point_id+i);
				}
				last_used_point_id += 4;

				cellArray->InsertNextCell(pyras[pyra_count]);
    			unstructuredGrids[poly_count]->SetCells(VTK_PYRAMID, cellArray);

				mappers[poly_count] = vtkSmartPointer<vtkDataSetMapper>::New();
				mappers[poly_count]->SetInputData(unstructuredGrids[poly_count]);

				actors[poly_count] = vtkSmartPointer<vtkActor>::New();
				actors[poly_count]->SetMapper(mappers[poly_count]);
				actors[poly_count]->GetProperty()->SetColor(colors->GetColor3d("Cyan").GetData());
				renderer->AddActor(actors[poly_count]);

				// actors[poly_count]->GetProperty()->SetColor( colors->GetColor3d("Red").GetData());

				pyra_count++;
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
	renderer->SetBackground( colors->GetColor3d("Grey").GetData() );

        // Setup the light
        light = vtkSmartPointer<vtkLight>::New();
        light->SetLightTypeToHeadlight();
        light->SetIntensity( 1 );

	// Setup the renderers's camera
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Azimuth(30);
	renderer->GetActiveCamera()->Elevation(30);
	renderer->ResetCameraClippingRange();
	
	
	ui->sa->setIcon(QIcon("ModelLoader/src/gui/Icons/filesave.png")); //choose the icon location

	// Render and interact
	// renderWindow->Render();					// ###### Not needed with Qt ######
	// renderWindowInteractor->Start();			// ###### Not needed with Qt ######
	qInfo() << "Window complete"; // debug

	connect( ui->greenButton,SIGNAL(clicked()), this, SLOT(on_greenButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position) //light
{
    light->SetIntensity((float) (100-position)/100);
    ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_comboBox_activated(const QString &arg1) //camera
{
    if (arg1 == "+X-Axis"){
           renderer->GetActiveCamera()->SetPosition(1.0,0.0,0.0);
       }
       else if (arg1 == "-X-Axis"){
            renderer->GetActiveCamera()->SetPosition(-1.0,0.0,0.0);
       }
       else if (arg1 == "+Y-Axis"){
            renderer->GetActiveCamera()->SetPosition(0.0,1.0,0.0);
       }
       else if (arg1 == "-Y-Axis"){
            renderer->GetActiveCamera()->SetPosition(0.0,-1.0,0.0);
       }
       else if (arg1 == "+Z-Axis"){
            renderer->GetActiveCamera()->SetPosition(0.0,0.0,1.0);
       }
       else if (arg1 == "-Z-Axis"){
            renderer->GetActiveCamera()->SetPosition(0.0,0.0,-1.0);
       }
       renderer->ResetCamera();
       ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::handleModelButton()
{
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

	QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");

	if (color.isValid()) {

		QString hex = color.name();
		std::string str = hex.toStdString();
		char *cstr = &str[0u];

		int r, g, b;
		double ri, gi, bi;
		sscanf(cstr, "#%02x%02x%02x", &r, &g, &b);

		ri = (double)r / 255;
		gi = (double)g / 255;
		bi = (double)b / 255;

		actor->GetProperty()->SetColor(ri, gi, bi);
	}

    ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::handleBackgButton()
{
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    renderer->AddActor(actor);

    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");

    if(color.isValid()) {

		QString hex = color.name();

		std::string str = hex.toStdString();
		char *cstr = &str[0u];

		int r, g, b;
		double ri, gi, bi;

		sscanf(cstr, "#%02x%02x%02x", &r, &g, &b);

		ri = (double)r / 255;
		gi = (double)g / 255;
		bi = (double)b / 255;

        renderer->SetBackground(ri, gi, bi);
    }

    ui->qvtkWidget->GetRenderWindow()->Render();
}
  
void MainWindow::on_sa_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png)")); 
        QScreen *screen = QGuiApplication::primaryScreen();
        screen->grabWindow(ui->qvtkWidget->winId()).save(filename);

}

void MainWindow::on_greenButton_clicked()
{
    //actor->GetProperty()->SetColor( colors->GetColor3d("green").GetData() );
    ui->qvtkWidget->GetRenderWindow()->Render();
}




//Code for File Open, Save, help and print

//Open file Code
void MainWindow::on_actionFileOpen_triggered()
{


}
//Save file code
void MainWindow::on_actionFileSave_triggered()
{

}

//Help button code
//Could possibly contain an readme file or a html link to instructions on how to use the software
void MainWindow::on_actionHelp_triggered()
{

}

//
void MainWindow::on_actionPrint_triggered()
{

}



//Colour scrollers (R,G,B)
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{

}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{

}

void MainWindow::on_horizontalSlider_3_sliderMoved(int position)
{
}