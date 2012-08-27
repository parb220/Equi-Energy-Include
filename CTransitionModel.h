#ifndef TRANSITION_MODEL
#define TRANSITION_MODEL

#include <vector>
#include <gsl/gsl_rng.h>

using namespace std;
class CTransitionModel 
{
public:
	virtual double log_prob(const double *x, const double *y, int dim)=0; 
	virtual double draw(double *y, int dim, bool &if_new_sample, const double *x, double log_prob_x, const gsl_rng* r, int B=0)=0;	// draw a sample to put into y given x
	virtual void tune_step_size(double, int =-1) = 0; 
	virtual double get_step_size(int =-1) = 0; 
	virtual void set_step_size(double, int=-1) = 0; 
};
#endif
