//: plotter.cpp
#include <iostream>
#include "plotter.h"

/* Various include statements for plot_line: */
#include <vtkVersion.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartXY.h>
#include <vtkTable.h>
#include <vtkPlot.h>
#include <vtkDoubleArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkPen.h>
/*-----------------------------------------*/

Plotter::Plotter(){
	// Do nothing
}

/* -------------------------------- */
/*			PLOT_LINE									  */
/* -------------------------------- */
void Plotter::plot_line(double *x, double *y, int num_points){
  vtkSmartPointer<vtkTable> table = 
    vtkSmartPointer<vtkTable>::New();

  vtkSmartPointer<vtkDoubleArray> arrX = 
    vtkSmartPointer<vtkDoubleArray>::New();
  arrX->SetName("x-axis");
  table->AddColumn(arrX);

  vtkSmartPointer<vtkDoubleArray> arrY = vtkSmartPointer<vtkDoubleArray>::New();
  arrY->SetName("y-axis");
  table->AddColumn(arrY);

  // Fill the table with values
  table->SetNumberOfRows(num_points);
  for (int i=0; i<num_points; ++i){
    table->SetValue(i, 0, x[i]);
    table->SetValue(i, 1, y[i]);
  }

  // Set up the view
  vtkSmartPointer<vtkContextView> view =
    vtkSmartPointer<vtkContextView>::New();
  view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);

  // add line plot
  vtkSmartPointer<vtkChartXY> chart =
    vtkSmartPointer<vtkChartXY>::New();

  view->GetScene()->AddItem(chart);
  vtkPlot *line = chart->AddPlot(vtkChart::LINE);

  #if VTK_MAJOR_VERSION <= 5
    line->SetInput(table, 0, 1);
  #else
    line->SetInputData(table, 0, 1);
  #endif
    line->SetColor(0, 255, 0, 255);
    line->SetWidth(1.5);

  // Start interactor
  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();

}
  

