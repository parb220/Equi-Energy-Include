#ifndef TRANSITION_MODEL_SIMPLE_GAUSSIAN
#define TRANSITION_MODEL_SIMPLE_GAUSSIAN

#include <vector>
#include <gsl/gsl_rng.h>
#include "CSimpleGaussianModel.h"
#include "CTransitionModel.h"

using namespace std;

class CTransitionModel_SimpleGaussian : public CTransitionModel, protected CSimpleGaussianModel
{
public: 
	CTransitionModel_SimpleGaussian(int dim=0): CSimpleGaussianModel(dim) {} 
	CTransitionModel_SimpleGaussian(int dim, const double *s):CTransitionModel(), CSimpleGaussianModel(dim) { CSimpleGaussianModel::SetSigmaParameter(s,dim);}
	~CTransitionModel_SimpleGaussian() {}

	virtual double log_prob(const double *, const double *, int); 
	virtual double draw(double *, int, bool &, const double *, double, const gsl_rng *, int B=0); 
	virtual void tune_step_size(double, int =-1); 
	virtual void set_step_size(double _s, int =-1); 
	virtual double get_step_size(int _dim=-1); 
};

/*
 p(y|x) = N(; x, sigma) 
y: new sample
x: given sample
sigma: standard deviation
 */

#endif
