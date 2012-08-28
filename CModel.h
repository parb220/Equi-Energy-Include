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
	virtual double draw(double *, int, bool &, const gsl_rng *, const double *old_x = NULL, double old_log_prob=0, int B=0)=0 ; 
	/* double *:		buffer to hold the new sample
 	   int:			size of buffer
	   bool &:		true if new sample
	   const gsl_rng *:	random number generator
	   const double *:	current sample
	   double:		log prob of current sample
	   int:			number of tries 
	   return:		log_prob of new sample
	*/
	

	/* MH */
	virtual double draw(CTransitionModel *, double *, int, bool &, const gsl_rng *, const double *, double, int B=0) ;  
	/*
	CTransitionModel *:	proposal distribution
	double *: 		buffer to hold the new sample
	int:			size of buffer
	bool &:			whether it is a new sample
	const gsl_rng *:	random number generator 
	const double *:		current sample
	double:			log prob of current sample
	int:			number of tries for the multiple-try MH	
	return:			log_prob of new sample
 	*/
	
	/* MH on blocks of dimensions */
	virtual double draw(CTransitionModel **, double *, int, vector <bool> &,  const gsl_rng *, const double *, double, int, const vector <int> &, int mMH=0) ; 
	/*
	CTransitionModel **:	array of distribution models, each for a block
	double *:		buffer to hold the new sample
	int:			size of buffer
	vector<bool>:		vector of flags indicating which blocks are updated
	const gsl_rng *:	random number generator
	const double *:		current sample
	double:			log prob of current sample
 	int:			number of blocks
	const vector<int> &:	vector of block sizes
	int:			number of tries
 	return:			log_prob of the new sample	
	*/

	// MH on one block while keep the other blocks fixed
	virtual double draw_block(int, int, CTransitionModel *, double *, int, bool &, const gsl_rng *, const double *, double, int mMH=0) ; 
	/*
 	int:			offset of array	
	int:			size of block to be udpated
	CTransitionModel:	distribution model for the block of interest
	double *:		buffer to hold the new sample, where only one block will be changed while other blocks remain unchanged
	int:			size of buffer
	bool:			flag indicating whether the block is updated
	const gsl_rng *:	random number generator
	const double *:		current sample
	double:			log_prob of current sample
	int:			number of tries
	return:			log_prob of the new sample
 	*/

	int GetDataDimension() const { return nData; }
	int GetParameterNumber() const { return nParameter;}
	
	virtual void SetDataDimension(int nD) { nData = nD; }
	void SetParameterNumber(int nP) { nParameter = nP; }

	virtual void GetMode(double *, int, int iMode =0) = 0; 
	/*
 	double *:	buffer to hold the mode
	int:		size of buffer
	int:		index of Mode; used for CMixtureModel to determine which component's mode to use 
 	*/
};

#endif
