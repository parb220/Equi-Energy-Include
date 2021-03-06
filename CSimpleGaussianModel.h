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
		virtual ~CSimpleGaussianModel(); 

		virtual void SetDataDimension(int); 
		void SetMeanParameter(const double *, int); 
		void SetSigmaParameter(const double *, int); 
		double GetSigmaParameter(int i) const {return sigma[i]; }
		virtual double log_prob(CSampleIDWeight &) const; 
		virtual void draw(CSampleIDWeight &, bool &, const gsl_rng *, int B=0) const;
		virtual void GetMode(CSampleIDWeight &, int iModel=0) const; 
};

#endif
