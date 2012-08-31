#ifndef TRANSITION_MODEL
#define TRANSITION_MODEL

#include <vector>
#include <gsl/gsl_rng.h>
#include "CSampleIDWeight.h"

class CModel; 

class CTransitionModel 
{
public:
	virtual double log_prob(const CSampleIDWeight &x, const CSampleIDWeight &y) const=0; 
	virtual void draw(CSampleIDWeight&, bool &if_new_sample, const gsl_rng *r, const CSampleIDWeight &x, int B=0) const=0;	// draw a sample to put into y given x

	virtual double get_step_size(int =-1) const= 0; 
	virtual void set_step_size(double, int=-1) = 0; 

	virtual void Tune(double acc, int lPeriod, int nPeriod, const gsl_rng *r, CModel *targetModel, CSampleIDWeight &x, int dim_lum_sum, int block_size) = 0;
	/*
 	double:			target acceptance rate
	int:			length of observational period
	int:			number of observational periods
	const gsl_rng*:		random number generator
	const CModel*:		target distribution model
	CSampleIDWeight &:	start point
	int:			offset of X (starting from which dimension X is tuned)
	int:			size of dimensions to be tuned (how many dimensions of X are tuned)
 	*/
};
#endif
