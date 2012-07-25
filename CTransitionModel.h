#ifndef TRANSITION_MODEL
#define TRANSITION_MODEL

#include <vector>
#include <gsl/gsl_rng.h>

using namespace std;
class CTransitionModel 
{
public:
	virtual double log_prob(const double *x, const double *y, int dim)=0; 
	virtual double draw(double *y, int dim, const double *x, const gsl_rng* r, int B=0)=0;	// draw a sample to put into y given x
	virtual void step_size_tune(double) = 0; 
	virtual double get_step_size() = 0; 
};
#endif
