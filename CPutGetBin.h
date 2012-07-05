#ifndef _PUT_GET_BIN_
#define _PUT_GET_BIN_

#include <string>
#include <vector>
#include <gsl/gsl_rng.h>
#include "CSampleIDWeight.h"

using namespace std; 

class CPutGetBin					 
{
private: 
	int id; 
	int nSamplesGeneratedByFar;		// total number of samples generated by far 
	int capacityPut; 			// capacity of this bin for put (does not have to be same as capacity for get), we will set capacityPut >= capacityGet;
	int capacityGet; 			// capacity of this bin for get 
	int nPutUsed; 			// available space for put (will be reset as capacityPut after each dump, and will decrease as a sample is depoisited)
	int nGetUsed; 			// available data for get (will be reset as capacityGet after each fetch, and will decrease as a sample is drawn)	
	string filename_prefix; 		// run_id.bin_id.index (index = nSampleGeneratedByFar/capacity); 
	vector <CSampleIDWeight> dataPut; 	// space for put
	vector <CSampleIDWeight> dataGet; 	// data for get 

	bool Dump(int); 			// dump the current materials to file;
	bool Fetch(const gsl_rng*); 
 	bool ReadFromOneFile(int, int &, const vector <int> &index);
	int GetNumberDataFile() const { return nSamplesGeneratedByFar/capacityPut; }
public: 
	CPutGetBin(int _id=0, int _nTotalSamples=0, int _capacityPut=0, int _capacityGet=0, string _grandPrefix=""); 
	~CPutGetBin();

	void SetBinID(int _id) { id = _id; }
	int GetBinID() const { return id; }

	void SetNumberSamplesGeneratedByFar(int _nTotalSamples) { nSamplesGeneratedByFar = _nTotalSamples; }
	int GetNumberSamplesGeneratedByFar() const { return nSamplesGeneratedByFar; }

	void SetCapacity_Put (int);
	int GetCapacity_Put() const { return capacityPut; }
	
	void SetCapacity_Get(int); 
	int GetCapacity_Get() const { return capacityGet; }
	
	int GetNumberDataFile(bool) const; 	
	void SetFileNamePrefix(string _grandPrefix) { filename_prefix = _grandPrefix; } 
	string GetFileNamePrefix() const { return filename_prefix;}	

	int DepositSample(const CSampleIDWeight &); 
	int DepositSample(const double *, int, int, double _weight=1.0); 

	CSampleIDWeight DrawSample(const gsl_rng *); 
	void DrawSample(double *, int, int &, double &, const gsl_rng *);  

	void finalize(); 	// save unsaved data

	/* for reassigning samples into different bins */ 
	vector <CSampleIDWeight> RetrieveSamplesSequentially(bool); 
	void ChangeFileName(int);
}; 

#endif
