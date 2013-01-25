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
	int cluster_node;
	int run_id; 
	int get_marker; 
	int put_marker; 
	int number_bins; 
	vector <CPutGetBin> bin; 
	string filename_base; 
public: 
	CStorageHead(int _run_id = 0, int _get_marker = 100, int _put_marker = 100, int _number_bins = 1, string file=string(""), int _node_index=0); 
	virtual ~CStorageHead(); 

	virtual int DepositSample(int, const CSampleIDWeight &) ; 
	virtual int DepositSample(int, const double *, int, int, double _weight=1.0) ;

	virtual bool DrawLeastWeightSample(int, CSampleIDWeight &) const; 
	virtual bool DrawLeastWeightSample(int, double *, int, int &, double &) const;  
	virtual bool DrawMostWeightSample(int, CSampleIDWeight &)const; 
	virtual bool DrawMostWeightSample(int , double *, int, int &, double &) const; 
	virtual bool DrawSample(int, const gsl_rng *, CSampleIDWeight &) ; 
	virtual bool DrawSample(int, double *, int, int &, double &, const gsl_rng *) ;  
	bool makedir(); 
	void finalize(int =-1,  int =-1)  ;
	int GetNumberBins() const { return number_bins; }
	int GetNumberRecrod(int index) const { return bin[index].GetTotalNumberRecord(); }

	/* for reassigning samples into different bins */
	virtual void DisregardHistorySamples(int = -1, int = -1); 
	virtual void ClearDepositDrawHistory(int = -1, int = -1); 
	virtual void consolidate(int = -1, int = -1); 
	void restore(int = -1, int = -1);
	void RestoreForFetch(int = -1, int = -1); 
	bool empty(int = -1, int = -1) const; 

	friend void CParameterPackage::TraceStorageHead(const CStorageHead &); 
	friend bool CParameterPackage::LoadCurrentStateFromStorage(CStorageHead &, const gsl_rng *, int=-1); 
}; 

#endif
