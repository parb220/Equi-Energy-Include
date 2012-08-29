#ifndef ENERGY_BOUNDED_FROM_BELOW_NORMALIZED_BY_TEMPERATURE
#define ENERGY_BOUNDED_FROM_BELOW_NORMALIZED_BY_TEMPERATURE

#include <gsl/gsl_rng.h>
#include "CModel.h"

class CBoundedModel : public CModel 
{
private:
	double 	H;	// Lower bound of energy 
	double 	T;	// Temperature for normalization
	CModel *OriginalModel; 	// Original model to get energy 
public: 
	CBoundedModel(double h = 0, double t =0, CModel *original=NULL); 
	virtual double log_prob(const double*, int) ; 
	virtual double log_prob(CSampleIDWeight &x); 
	virtual double energy(const double*, int) ; 
	virtual double energy(CSampleIDWeight &x); 
	void SetH(double); 
	void SetT(double); 
	virtual double draw(double *, int, bool &, const gsl_rng*, int mMH=0);  // OriginalModel->draw 
	virtual void GetMode(double *, int, int iModel =0); 
};  

#endif
