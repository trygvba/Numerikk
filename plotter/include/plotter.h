//: plotter.h
#ifndef PLOTTER_H
#define PLOTTER_H

class Plotter {
  public:
    Plotter();
    ~Plotter();
    void plot_line(double* x, double* y, int num_points);
};
#endif // PLOTTER_H
