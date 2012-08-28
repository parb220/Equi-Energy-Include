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
	virtual double draw(double *, int, bool &, const gsl_rng *, const double *, double, int =0); 
	virtual void set_step_size(double _s, int =-1); 
	virtual double get_step_size(int _dim=-1); 

	virtual void Tune(double, int, int, const gsl_rng *, CModel *, const double *, int, double, int, int);

protected:
	void TuneDimension(double, int, int, const gsl_rng *r, CModel *, const double *, int, double, int , int );
	/* Tune one dimension of sigma of SimpleGaussian 
 	double:			target acceptance rate
	int:			length of observational period
	int:			number of observational period
	const gsl_rng *:	random number generator
	const CModel:		target distribution model
	const double *:		start point 
	int:			size of the above array
	double:			log_prob of start point
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
