#ifndef UNIFORM_DISTRIBUTION_H
#define UNIFORM_DISTRIBUTION_H

#include <gsl/gsl_rng.h>
#include "CModel.h" 

using namespace std;

class CUniformModel : public CModel
{
protected: 
	double *lower_bound; 
	double *upper_bound; 
	
	virtual double log_prob_raw(const double*, int) const; 
	virtual double draw_raw(double*, int, bool &, const gsl_rng*, int =0) const;
	virtual void GetMode_raw(double *, int, int iMode =0) const; 
public:
	CUniformModel(int nD=0); 
	CUniformModel(int, const double*, const double*); 
	~CUniformModel(); 

	virtual void SetDataDimension(int);  
	void SetLowerBoundParameter(const double*, int); 
	void SetUpperBoundParameter(const double*, int); 

}; 

#endif
