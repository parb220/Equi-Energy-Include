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
	virtual double log_prob(const vector <double > &); 
	virtual double energy(const double*, int) ; 
	virtual double energy(const vector <double > &);
	void SetH(double); 
	void SetT(double); 
	virtual int draw(double *, int, const gsl_rng*, const double *old_x =NULL, int B=0);  // OriginalModel->draw 
	virtual vector <double> draw(const gsl_rng *, const vector <double> &x =vector<double>(0), int B=0); // OriginalModel->draw
};  

#endif
