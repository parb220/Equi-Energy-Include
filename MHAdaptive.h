#ifndef _MH_ADAPTIVE_
#define _MH_ADAPTIVE_

#include <vector>
using namespace std;

struct AccStep {
	int nGenerated; 
	int nAccepted;
        double acc;
        double step;
};

class MHAdaptive
{
// Dan's method
protected:
	int period; 
	double scale; 
	double best_scale; 
	double low_scale; 
	double high_scale; 
	double low_jump_ratio; 
	double high_jump_ratio; 

	double mid; 
	double log_mid; 
	double lower_bound; 
	double upper_bound; 
	double previous_ratio;
public: 
	MHAdaptive(int _periodL, double _targetProb, double _a=-3.0, double _b =3.0); 
	//period,  mid
	void UpdateScale(int _g, int _a);
	// _g: new number of generated samples
	// _n: new number of accepted samples 
	
	double GetScale() const { return scale; }
	double GetBestScale() const { return best_scale; }
	int GetPeriodLength() const { return period; }
/* Regression method based on Graves "Automatic step size selection in random
 * walk metroplolis algorithm */
protected:
	// logit(acceptace rate with step size s) = a +b log(s)
	// logit(x) = log(x)-log(1-x)
	double a, b; // starting value of a and b better satisfy a+b =0
	double A, B, C; // used in UpdateRegressionParameter
	double sum_diff_p; // sum_i (nAccepted-nGenerated*estimatedP), also used in UpdateRegressionParameter
	double sum_log_diff_p; 	// sum_i log(scale) *(nAccepted-nGenerated*estimatedP)
public:
	void EstimateRegressionParameters(vector<AccStep> &); 
	double GetStepSizeRegression() const; 
	double GetStepSize(vector <AccStep>&); 
}; 

#endif
