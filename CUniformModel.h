#ifndef UNIFORM_DISTRIBUTION_H
#define UNIFORM_DISTRIBUTION_H

#include <gsl/gsl_rng.h>
#include "CModel.h" 

using namespace std;

class CUniformModel : public CModel
{
private: 
	double *lower_bound; 
	double *upper_bound; 
	
public:
	CUniformModel(int nD=0); 
	CUniformModel(int, const double*, const double*); 
	CUniformModel(const vector <double> &, const vector < double> &); 
	~CUniformModel(); 
 
	void SetLowerBoundParameter(const double*, int); 
	void SetLowerBoundParameter(const vector < double > &); 
	void SetUpperBoundParameter(const double*, int); 
	void SetUpperBoundParameter(const vector < double > &);

	virtual double log_prob(const double*, int); 
	virtual double log_prob(const vector <double > &); 
	virtual int draw(double*, int, const gsl_rng*, const double *old_x = NULL, int B=0);
	vector < double > draw(const gsl_rng*, const vector <double> &old_x = vector<double>(0), int B=0); 
}; 

#endif
