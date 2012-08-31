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

	virtual void set_step_size(double _s, int =-1); 
	virtual double get_step_size(int _dim=-1) const; 

	virtual double log_prob(const CSampleIDWeight &x, const CSampleIDWeight &y) const; 
	virtual void draw(CSampleIDWeight &, bool &, const gsl_rng *, const CSampleIDWeight &, int =0) const; 
	virtual void Tune(double, int, int, const gsl_rng *, CModel *, CSampleIDWeight &, int, int);
	void TuneDimension(double, int, int, const gsl_rng *r, CModel *, CSampleIDWeight &,  int , int );
	/* Tune one dimension of sigma of SimpleGaussian 
 	double:			target acceptance rate
	int:			length of observational period
	int:			number of observational period
	const gsl_rng *:	random number generator
	const CModel:		target distribution model
	CSampleIDWeight &:	start point
	int:			offset along X (at which dimension of x)
	int:			offset along Propoal (at which dimension of proposal model)		
 	*/
};

/*
 p(y|x) = N(; x, sigma) 
y: new sample
x: given sample
sigma: standard deviation
 */

#endif
