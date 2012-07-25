#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <gsl/gsl_rng.h>
#include "CTransitionModel.h"

using namespace std; 

class CModel
{
protected:
	int nData; 			// Dimension of data
	int nParameter; 		// Number of Parameters
public:
	CModel(int nD=0, int nP=0)
	{
		nData = nD; 
		nParameter = nP; 
	}

	virtual double log_prob(const double *, int)=0 ;
	virtual double log_prob(const vector <double > &)=0; 

	virtual double energy(const double *, int) ; 
	virtual double energy(const vector <double > &);  

	/* Draw a new sample based on an old sample (without proposal model) */
	virtual int draw(double *, int, const gsl_rng *, const double *old_x = NULL, int B=0)=0 ; 
	virtual vector < double >draw (const gsl_rng *, const vector <double> & old_x = vector <double>(0), int B=0) = 0; 
	/* double *:		buffer to hold the new sample
 	   int:			size of buffer
	   const gsl_rng *:	random number generator
	   const double *:	current sample
	   int:			number of tries 
	   return:		dimension of the newly generated sample
	*/
	

	/* MH */
	virtual int draw(CTransitionModel *, double *, int, const double *, const gsl_rng *, bool &new_sample_flag, int B=0); 
	virtual vector < double >draw (CTransitionModel *, const vector < double > &, const gsl_rng *, bool &new_sample_flag, int B=0); 
	/*
	CTransitionModel *:	proposal distribution
	double *: 		buffer to hold the new sample
	int:			size of buffer
	const double *:		current sample
	const gsl_rng *:	random number generator 
	bool &:			whether it is a new sample
	int:			number of tries for the multiple-try MH	
	return:			dimension of the newly created sample if successful; otherwise -1
 	*/
	
	/* MH on blocks of dimensions */
	virtual int draw(int, const int *, CTransitionModel **, double *, int, const double *, const gsl_rng *, bool *, int B=0); 
	/*
 	int:			number of blocks
	const int *:		array of block sizes
	CTransitionModel **:	array of distribution models, each for a block
	double *:		buffer to hold the new sample
	int:			size of buffer
	const double *:		current sample
	bool *:			array of flags indicating which blocks are updated
	int:			number of tries
 	*/


	int GetDataDimension() const { return nData; }
	int GetParameterNumber() const { return nParameter;}
	
	void SetDataDimension(int nD) { nData = nD; }
	void SetParameterNumber(int nP) { nParameter = nP; }
};

#endif
