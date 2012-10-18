#ifndef _STORAGE_HEAD_PTHREAD  
#define _STORAGE_HEAD_PTHREAD

#include <pthread.h>
#include <vector>
#include "CStorageHead.h"
#include "CSampleIDWeight.h"

using namespace std; 

class CStorageHeadPthread : public CStorageHead
{
public: 
	vector <pthread_mutex_t> mutex; 
	
	CStorageHeadPthread(int _run_id = 0, int _get_marker = 100, int _put_marker = 100, int _number_bins = 1, string file=string(""), int _node_index=0); 
	virtual ~CStorageHeadPthread(); 
	
 	virtual	int DepositSample(int, const CSampleIDWeight &);        
        virtual int DepositSample(int, const double *, int, int, double _weight=1.0);

        virtual bool DrawSample(int, const gsl_rng *, CSampleIDWeight &);        
        virtual bool DrawSample(int, double *, int, int &, double &, const gsl_rng *);      
};

#endif
