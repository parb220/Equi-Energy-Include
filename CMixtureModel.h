#ifndef MIXTURE_MODEL
#define MIXTURE_MODEL

#include <gsl/gsl_rng.h>
#include "CModel.h"

class CMixtureModel : public CModel
{
protected:
	int nModel; 		// Number of models;
	CModel **model;		// array of pointers to models; 
	double *weight; 	// weight of each component; 
	virtual double log_prob_raw(const double *, int) const; 
	virtual double draw_raw(double *, int, bool &, const gsl_rng *, int =0) const; 	 
	virtual void GetMode_raw(double *,int, int iMode=0) const; 
public: 
	CMixtureModel(int nD=0, int nP=0, int nM=0, double *w = NULL); 
	~CMixtureModel(); 

	CModel * operator[] (int) const; // Get the pointer to the i-th model; 	
	void Initialize(int, CModel *); // Let the i-th model point to the argument;    
	int SetWeightParameter(const double *, int);
	void SetModelNumber(int);  
	int GetModelNumber() const { return nModel; }
	void CalculateSetParameterNumber() ;
};
#endif
