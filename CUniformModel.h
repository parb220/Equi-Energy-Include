#ifndef UNIFORM_DISTRIBUTION_H
#define UNIFORM_DISTRIBUTION_H

#include <gsl/gsl_rng.h>
#include "CModel.h" 

using namespace std;

class CUniformModel : public CModel
{
private: 
	double *lower_bound; 
	double *upper_bound; 
	
public:
	CUniformModel(int nD=0); 
	CUniformModel(int, const double*, const double*); 
	~CUniformModel(); 

	virtual void SetDataDimension(int);  
	void SetLowerBoundParameter(const double*, int); 
	void SetUpperBoundParameter(const double*, int); 

	virtual double log_prob(const double*, int); 

	virtual double draw(double*, int, bool &, const gsl_rng*, const double * = NULL, double =0, int =0);
	virtual void GetMode(double *, int, int iMode =0); 
}; 

#endif
