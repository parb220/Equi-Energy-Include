#ifndef _TRANSITION_MODEL_GAUSSIAN
#define _TRANSITION_MODEL_GAUSSIAN

#include <gsl/gsl_rng.h>
#include "CTransitionModel_SimpleGaussian.h"
#include "CGaussianModel.h"

class CTransitionModel_Gaussian : public CTransitionModel, protected CGaussianModel
{
public:
	CTransitionModel_Gaussian(int _dim=0) : CTransitionModel(), CGaussianModel(_dim) {} 
	CTransitionModel_Gaussian(int _dim, const double *_covariance) : CTransitionModel(), CGaussianModel(_dim, NULL, _covariance) {}  
	~CTransitionModel_Gaussian() {} 

	virtual double log_prob(const CSampleIDWeight &x, const CSampleIDWeight &y) const; 
	virtual void drawMH(CSampleIDWeight &, bool &, const gsl_rng *, const CSampleIDWeight &, int mMH=0) const; 

	virtual void set_step_size(double _s, int = -1); 
	virtual double get_step_size(int _dim=-1) const; 
	virtual void Tune(double, int, int, const gsl_rng *, const CModel *, const CSampleIDWeight &, int, int); 
}; 

#endif
