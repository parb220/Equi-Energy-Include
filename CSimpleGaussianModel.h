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
		virtual double log_prob_raw(const double *, int) const; 
		virtual double draw_raw(double *, int, bool &, const gsl_rng *, int B=0) const;
		virtual void GetMode_raw(double *, int, int iModel=0) const; 
public:
		CSimpleGaussianModel(int dim = 0);
		CSimpleGaussianModel(int, const double *, const double *); 
		~CSimpleGaussianModel(); 

		virtual void SetDataDimension(int); 
		void SetMeanParameter(const double *, int); 
		void SetSigmaParameter(const double *, int); 
		double GetSigmaParameter(int i) const {return sigma[i]; }
};

#endif
