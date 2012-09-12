#ifndef _STORAGE_HEAD_
#define _STORAGE_HEAD_

#include <vector>
#include <string>
#include <gsl/gsl_rng.h>
#include "CPutGetBin.h"
#include "CSampleIDWeight.h"
#include "CParameterPackage.h"

using namespace std; 

class CStorageHead
{
protected:
	int run_id; 
	int get_marker; 
	int put_marker; 
	int number_bins; 
	vector <CPutGetBin> bin; 
	string filename_base; 
public: 
	CStorageHead(int _run_id = 0, int _get_marker = 100, int _put_marker = 100, int _number_bins = 1, string file=string("")); 
	~CStorageHead(); 

	virtual int DepositSample(int, const CSampleIDWeight &); 
	virtual int DepositSample(int, const double *, int, int, double _weight=1.0);

	virtual bool DrawSample(int, const gsl_rng *, CSampleIDWeight &); 
	virtual bool DrawSample(int, double *, int, int &, double &, const gsl_rng *);  
	bool empty(int); 
	bool makedir(); 
	void finalize();
	int GetNumberBins() const { return number_bins; }

	/* for reassigning samples into different bins */
	virtual void DisregardHistorySamples(int); 
	virtual void ClearDepositDrawHistory(int); 
	void restore();

	friend void CParameterPackage::TraceStorageHead(const CStorageHead &); 
}; 

#endif
