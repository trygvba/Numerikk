//: plotter.h
// Class for various plotting procedures.
#ifndef PLOTTER_H
#define PLOTTER_H
class Plotter {
	// No class variables just yet.
	public:
		Plotter();		// Both constructor 
		~Plotter();		// and destructor don't need to do anything.

		void plot_line(double* x, double* y, int num_points);
};
#endif // PLOTTER_H
