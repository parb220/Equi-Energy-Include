#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <gsl/gsl_rng.h>
#include "CTransitionModel.h"
#include "CSampleIDWeight.h"

using namespace std; 

class CModel
{
protected:
	int nData; 			// Dimension of data
	int nParameter; 		// Number of Parameters
	virtual void CalculateLogProb(CSampleIDWeight &x) const;
	virtual double log_prob_raw(const double *x, int nX) const =0;
	virtual double energy_raw(const double *x, int nX) const; 
	/* Draw a new sample based on an old sample (without proposal model) */
	virtual double draw_raw(double *, int, bool &, const gsl_rng *, int B=0) const =0; 
	/* double *:		buffer to hold the new sample
 	   int:			size of buffer
	   bool &:		true if new sample
	   const gsl_rng *:	random number generator
	   int:			number of tries 
	   return:		log_prob of new sample
	*/
	
	virtual void GetMode_raw(double *, int, int iMode =0) const = 0; 
	/*
 	double *:	buffer to hold the mode
	int:		size of buffer
	int:		index of Mode; used for CMixtureModel to determine which component's mode to use 
 	*/
public:
	CModel(int nD=0, int nP=0)
	{
		nData = nD; 
		nParameter = nP; 
	}

	virtual double log_prob(CSampleIDWeight &x) const; 

	virtual double energy(CSampleIDWeight &x) const; 

	/* Draw a new sample based on an old sample (without proposal model) */
	virtual CSampleIDWeight draw(bool &, const gsl_rng *r, int B=0) const; 

	/* MH */
	virtual CSampleIDWeight draw(CTransitionModel *, bool &, const gsl_rng *, CSampleIDWeight &, int mMH=0) const; 
	
	/* MH on blocks of dimensions */
	virtual CSampleIDWeight draw(CTransitionModel **, vector<bool> &, const gsl_rng *, CSampleIDWeight &, int, const vector<int> &, int mMH=0) const; 

	// MH on one block while keep the other blocks fixed
	virtual CSampleIDWeight draw_block(int, int, CTransitionModel *, bool &, const gsl_rng *, CSampleIDWeight &x, int mMH=0) const; 

	int GetDataDimension() const { return nData; }
	int GetParameterNumber() const { return nParameter;}
	
	virtual void SetDataDimension(int nD) { nData = nD; }
	void SetParameterNumber(int nP) { nParameter = nP; }

	virtual CSampleIDWeight GetMode(int iMode =0) const
	{
		CSampleIDWeight x; 
		x.SetDataDimension(nData); 
		GetMode_raw(x.GetData(), x.GetDataDimension(), iMode); 
		return x; 
	}
};

#endif
