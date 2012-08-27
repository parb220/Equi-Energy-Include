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

		virtual void SetDataDimension(int); 
		void SetMeanParameter(const double *, int); 
		void SetSigmaParameter(const double *, int); 
		double GetSigmaParameter(int i) const {return sigma[i]; }

		virtual double log_prob(const double *, int); 
		virtual double draw(double *, int, bool &, const gsl_rng *, const double * = NULL, double =0, int =0); 
		virtual void GetMode(double *, int, int iModel=0); 
};

#endif
