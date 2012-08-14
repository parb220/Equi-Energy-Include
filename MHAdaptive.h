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
	double old_scale; 
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
	MHAdaptive(double _targetProb, double _scale=1.0, double _a=1.12, double _b =-1.12); 
	bool UpdateScale(int _g, int _a);
	// _g: new number of generated samples
	// _n: new number of accepted samples 
	
	double GetScale() const { return scale; }
	double GetBestScale() const { return best_scale; }
	double GetUpperTargetAcceptanceRate() const { return upper_bound; }
	double GetLowerTargetAcceptanceRate() const { return lower_bound; }
	double GetTargetAcceptanceRate() const { return mid;}
	void ResetTargetAcceptanceRate(double); 
/* Regression method based on Graves "Automatic step size selection in random
 * walk metroplolis algorithm */
protected:
	// logit(acceptace rate with step size s) = a +b log(s)
	// logit(x) = log(x)-log(1-x)
	double a, b; // starting value of a and b better satisfy a+b =0
public:
	void EstimateRegressionParameters(const vector < AccStep > &); 
	double GetStepSizeRegression(int f=0) const;
	// f<0:	use lower_bound to calculate stepsize; 
	// f>0: use upper_bound to calculate stepsize; 
	// f=0: use mid to calculate stepsize 
}; 

#endif
