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

	virtual double energy(const double *, int) ; 

	/* Draw a new sample based on an old sample (without proposal model) */
	virtual double draw(double *, int, const gsl_rng *, const double *old_x = NULL, int B=0)=0 ; 
	/* double *:		buffer to hold the new sample
 	   int:			size of buffer
	   const gsl_rng *:	random number generator
	   const double *:	current sample
	   int:			number of tries 
	   return:		log_prob of new sample
	*/
	

	/* MH */
	virtual double draw(CTransitionModel *, double *, int, const double *, const gsl_rng *, bool &new_sample_flag, int B=0); 
	/*
	CTransitionModel *:	proposal distribution
	double *: 		buffer to hold the new sample
	int:			size of buffer
	const double *:		current sample
	const gsl_rng *:	random number generator 
	bool &:			whether it is a new sample
	int:			number of tries for the multiple-try MH	
	return:			log_prob of new sample
 	*/
	
	/* MH on blocks of dimensions */
	virtual double draw(CTransitionModel **, double *, int, const double *, const gsl_rng *, vector <bool> &, int, const vector <int> &, int mMH=0); 
	/*
	CTransitionModel **:	array of distribution models, each for a block
	double *:		buffer to hold the new sample
	int:			size of buffer
	const double *:		current sample
	vector<bool>:		vector of flags indicating which blocks are updated
	int:			number of tries
 	int:			number of blocks
	const int *:		vector of block sizes
 	return:			log_prob of the new sample	
	*/


	int GetDataDimension() const { return nData; }
	int GetParameterNumber() const { return nParameter;}
	
	void SetDataDimension(int nD) { nData = nD; }
	void SetParameterNumber(int nP) { nParameter = nP; }

	virtual void GetMode(double *, int, int iMode =0) = 0; 
	/*
 	double *:	buffer to hold the mode
	int:		size of buffer
	int:		index of Mode; used for CMixtureModel to determine which component's mode to use 
 	*/
};

#endif
