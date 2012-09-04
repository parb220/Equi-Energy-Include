#ifndef _GAUSSIAN_
#define _GAUSSIAN_

#include <gsl/gsl_rng.h>
#include "CSimpleGaussianModel.h"

class CGaussianModel : public CSimpleGaussianModel
{
protected:
	double *covariance_matrix; // A[i, j]: A[i*nData+j]; 
	double *transformation_matrix; // each column corresponds to an eigen vector
	void RotateByTransformationMatrix(double *, int, const double *) const; 
	void InverseRotateByTransformationMatrix(double *, int, const double *) const; 
	void TransformMean(); 
public:
	CGaussianModel(int dim=0, const double *_mean = NULL, const double *_covariance = NULL); 
	CGaussianModel(const CGaussianModel &); 
	const CGaussianModel & operator =(const CGaussianModel &); 
	~CGaussianModel(); 

	virtual void SetDataDimension(int); 
	virtual void SetCovarianceMatrix(const double *, int); 
	virtual void SetTransformationMatrix(const double *, int); 
	virtual void GetCovarianceMatrix(double *, int) const;  

	virtual double GetEigenValue(int _dim=0) const { return sigma[_dim]; } 
	virtual void GetEigenVector(double *, int, int =0) const; 
	virtual void GetEigenMatrix_Row(double *, int, int =0) const; 

	virtual double log_prob(CSampleIDWeight &x) const;  
	virtual void draw(CSampleIDWeight &, bool &, const gsl_rng *r, int mMH=0) const; 
	virtual void GetMode(CSampleIDWeight &, int iMode=0) const;  
	friend void EigenAnalysis(double *, double *, int, const double *); 
	/*
 * 	double *:	matrix to hold transformation matrix
 * 	double *:	array to hold eigen-values
 * 	int:		size of array
 * 	const double *:	array of covariance matrix
 * 	*/
}; 


#endif
