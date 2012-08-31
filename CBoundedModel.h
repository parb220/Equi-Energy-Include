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
	virtual void CalculateLogProb(CSampleIDWeight &) const; 
	virtual double log_prob_raw(const double*, int) const; 
	virtual double draw_raw(double *, int, bool &, const gsl_rng*, int mMH=0) const;  // OriginalModel->draw 
	virtual void GetMode_raw(double *, int, int iModel =0) const; 
public: 
	CBoundedModel(double h = 0, double t =0, CModel *original=NULL); 
	void SetH(double); 
	void SetT(double); 
	virtual CSampleIDWeight draw(bool &, const gsl_rng *, int mMH=0) const; 
};  

#endif
