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
	void SetH(double); 
	void SetT(double); 
	virtual double log_prob(CSampleIDWeight &) const; 
	virtual CSampleIDWeight draw(bool &, const gsl_rng*, int mMH=0) const;  // OriginalModel->draw 
	virtual CSampleIDWeight GetMode(int iModel =0) const; 
};  

#endif
