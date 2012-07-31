#ifndef SIMPLE_GAUSSIAN_MODEL
#define SIMPLE_GAUSSIAN_MODEL

#include <gsl/gsl_rng.h>
#include "CModel.h"

/*
 SimpleGaussianModel: independent among different dimesnions
 */

class CSimpleGaussianModel : public CModel
{
protected:	double *mu; 
		double *sigma; 
public:
		CSimpleGaussianModel(int dim = 0);
		CSimpleGaussianModel(int, const double *, const double *); 
		~CSimpleGaussianModel(); 

		void SetMeanParameter(const double *, int); 
		void SetSigmaParameter(const double *, int); 
		double GetSigmaParameter(int i) const {return sigma[i]; }

		virtual double log_prob(const double *, int); 
		virtual double draw(double *, int, const gsl_rng *, const double *old_x = NULL, int B=0); 
		virtual void GetMode(double *, int, int iModel=0); 
};

#endif
