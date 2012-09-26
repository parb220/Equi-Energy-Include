#ifndef _CLASS_STATE_MODEL
#define _CLASS_STATE_MODEL

#include <vector>
#include <gsl/gsl_rng.h>
#include "CModel.h"
#include "CTransitionModel.h"
#include "CSampleIDWeight.h"

extern "C" {
	#include "dw_switch.h"
}

using namespace std;

class CStateModel : public CModel
{
protected:
	TStateModel *model; 	// pointer to the TStateModel 
	int thetaDim; 		// dimension of theta, which refers to the state space parameters
	int qDim; 		// dimension of q, which refers to the transition matrix parameters
	CSampleIDWeight mode; 
public: 
	CStateModel(TStateModel * =NULL); 
	void SetModel(TStateModel * =NULL); 
	TStateModel * GetModel() const { return model; }
	void SetThetaDim(int _thetaDim) { thetaDim = _thetaDim; } 
	int GetThetaDim() const { return thetaDim; }
	void SetQDim(int _qDim) { qDim = _qDim; } 
	int GetQDim() const { return qDim; }

	/* theta and q are concatenated into the same vector 
 	where 0-(thetDim-1) are for theta, 
	and thetaDim - (thetaDim+qDim-1) are for q */
	virtual double log_prob(CSampleIDWeight &x) const; 

	// Transition model is not actually used. 
	// Instead, DrawAll of CStateModel will be used

	virtual void draw(CSampleIDWeight &, bool &, const gsl_rng *r, int B=0) const;
	virtual void GetMode(CSampleIDWeight &, int =0) const; 
};

#endif
