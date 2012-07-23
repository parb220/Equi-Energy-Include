#ifndef TRANSITION_MODEL
#define TRANSITION_MODEL

#include <vector>
#include <gsl/gsl_rng.h>

using namespace std;
class CTransitionModel 
{
public:
	virtual double log_prob(const double *x, const double *y, int dim)=0; 
	virtual double log_prob(const vector <double > &x, const vector <double > &y) = 0; 
	virtual int draw(double *y, int dim, const double *x, const gsl_rng* r)=0;	// draw a sample to put into y given x
	virtual vector < double > draw (const vector <double > &x, const gsl_rng *r)=0;
	virtual void step_size_tune(double) = 0; 
};
#endif
