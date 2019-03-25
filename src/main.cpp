#include <iostream>
#include <string>
#include <vector>
#include "cell.h"
#include "material.h"
#include "matrix.h"
#include "model.h"
#include "vector3d.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLWidget.h>
#include "gui/mainwindow.h"

int main( int argc, char** argv )
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat( QVTKOpenGLWidget::defaultFormat() );

  QApplication a( argc, argv );

  MainWindow window;
  window.show();

  return a.exec();
}