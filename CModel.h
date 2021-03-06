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
public:
	CModel(int nD=0, int nP=0)
	{
		nData = nD; 
		nParameter = nP; 
	}
	virtual ~CModel() {} 

	virtual double log_prob(CSampleIDWeight &x) const = 0; 

	virtual double energy(CSampleIDWeight &x) const; 

	/* Draw a new sample based on an old sample (without proposal model) */
	virtual void draw(CSampleIDWeight &, bool &, const gsl_rng *r, int B=0) const = 0; 

	/* MH */
	virtual void draw(CSampleIDWeight &, CTransitionModel *, bool &, const gsl_rng *, const CSampleIDWeight &, int mMH=0) const; 
	
	/* MH on blocks of dimensions */
	virtual void draw(CSampleIDWeight &, CTransitionModel **, vector<bool> &, const gsl_rng *, const CSampleIDWeight &, int, const vector<int> &, int mMH=0) const; 

	// MH on one block while keep the other blocks fixed
	virtual void draw_block(CSampleIDWeight &, int, int, CTransitionModel *, bool &, const gsl_rng *, const CSampleIDWeight &x, int mMH=0) const; 

	int GetDataDimension() const { return nData; }
	int GetParameterNumber() const { return nParameter;}
	
	virtual void SetDataDimension(int nD) { nData = nD; }
	void SetParameterNumber(int nP) { nParameter = nP; }

	virtual void GetMode(CSampleIDWeight &, int iMode =0) const = 0; 
};

#endif
