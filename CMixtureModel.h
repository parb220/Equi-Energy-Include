#ifndef MIXTURE_MODEL
#define MIXTURE_MODEL

#include <gsl/gsl_rng.h>
#include "CModel.h"

class CMixtureModel : public CModel
{
private: 
	int nModel; 		// Number of models;
	CModel **model;		// array of pointers to models; 
	double *weight; 	// weight of each component; 
public: 
	CMixtureModel(int nD=0, int nP=0, int nM=0, double *w = NULL); 
	~CMixtureModel(); 

	CModel * operator[] (int) const; // Get the pointer to the i-th model; 	
	void Initialize(int, CModel *); // Let the i-th model point to the argument;    
	int SetWeightParameter(const double *, int);
	void SetModelNumber(int);  
	int GetModelNumber() const { return nModel; }
	virtual double log_prob(const double *, int); 
	void CalculateSetParameterNumber();
	virtual double draw(double *, int, bool &, const gsl_rng *, int =0);	 
	virtual void GetMode(double *,int, int iMode=0); 
}; 

#endif
