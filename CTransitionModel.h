#ifndef TRANSITION_MODEL
#define TRANSITION_MODEL

#include <vector>
#include <gsl/gsl_rng.h>

using namespace std;
class CTransitionModel 
{
public:
	virtual double log_prob(const double *x, const double *y, int dim)=0; 
	virtual double draw(double *y, int dY, bool &if_new_sample, const gsl_rng *r, const double *x, double log_prob_x, int B=0)=0;	// draw a sample to put into y given x
	virtual void tune_step_size(double, int =-1) = 0; 
	virtual double get_step_size(int =-1) = 0; 
	virtual void set_step_size(double, int=-1) = 0; 

	virtual void Tune(double, int, int, const gsl_rng *, const CModel *, const double *, int, double, int, int) = 0; 
	/*
 	double:			target acceptance rate
	int:			length of observational period
	int:			number of observational periods
	const gsl_rng*:		random number generator
	const CModel*:		target distribution model
	const double*:		array holding the starting point 
	int:			size of the above array
	int:			offset of X (starting from which dimension X is tuned)
	int:			size of dimensions to be tuned (how many dimensions of X are tuned)
 	*/
};
#endif
