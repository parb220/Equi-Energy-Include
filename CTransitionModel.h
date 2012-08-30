#ifndef TRANSITION_MODEL
#define TRANSITION_MODEL

#include <vector>
#include <gsl/gsl_rng.h>
#include "CSampleIDWeight.h"

class CModel; 

class CTransitionModel 
{
public:
	virtual double log_prob(const double *x, const double *y, int dim)=0; 
	virtual double log_prob(CSampleIDWeight &x, CSampleIDWeight &y)
	{
		return log_prob(x.GetData(), y.GetData(), x.GetDataDimension()); 
	}

	virtual double draw(double *y, int dY, bool &if_new_sample, const gsl_rng *r, const double *x, double log_prob_x, int B=0)=0;	// draw a sample to put into y given x
	virtual CSampleIDWeight draw(bool &if_new_sample, const gsl_rng *r, CSampleIDWeight &x, int B=0)
	{
		CSampleIDWeight y; 
		y.SetDataDimension(x.GetDataDimension()); 
		y.log_prob = draw(y.GetData(), y.GetDataDimension(), if_new_sample, r, x.GetData(), x.log_prob, B); 
		return y; 
	}

	virtual double get_step_size(int =-1) = 0; 
	virtual void set_step_size(double, int=-1) = 0; 

	virtual void Tune(double, int, int, const gsl_rng *, CModel *, const double *, int, double, int, int) = 0; 
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
	virtual void Tune(double acc, int lPeriod, int nPeriod, const gsl_rng *r, CModel *targetModel, CSampleIDWeight &x, int dim_lum_sum, int block_size)
	{
		Tune(acc, lPeriod, nPeriod, r, targetModel, x.GetData(), x.GetDataDimension(), x.log_prob, dim_lum_sum, block_size); 
	}
};
#endif
