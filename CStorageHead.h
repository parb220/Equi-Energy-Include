#ifndef _STORAGE_HEAD_
#define _STORAGE_HEAD_

#include <vector>
#include <string>
#include <gsl/gsl_rng.h>
#include "CPutGetBin.h"
#include "CSampleIDWeight.h"

using namespace std; 

class CStorageHead
{
private:
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

	virtual CSampleIDWeight DrawSample(int, const gsl_rng *); 
	virtual void DrawSample(int, double *, int, int &, double &, const gsl_rng *);  
	bool empty(int); 
	string GetSummaryFileName() const; 
	friend ofstream & summary(ofstream &, const CStorageHead &); 
	bool makedir(); 
	void finalize();

	/* for reassigning samples into different bins */
	vector < CSampleIDWeight >RetrieveSamplesSequentially(bool, int); 
	virtual int DepositSample(bool, int, const CSampleIDWeight &); 
	virtual int DepositSample(bool, int, const double *, int, int, double _weight = 1.0); 
	virtual void Consolidate(int); 
	virtual void ClearTemporaryBin(); 
}; 

#endif
