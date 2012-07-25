#ifndef _CEES_PTHREAD
#define _CEES_PTHREAD

#include <gsl/gsl_rng.h>
#include <pthread.h>
#include <vector>
#include "CEES_Node.h"
#include "CTransitionModel.h"
#include "CStorageHeadPthread.h"

using namespace std; 

class CEES_Pthread : public CEES_Node
{
private: 
	static vector <pthread_cond_t> condition; 
	static vector <pthread_mutex_t> mutex; 
public: 	
	const gsl_rng *r; 
	static CStorageHeadPthread *storage;
	int simulationL; 
	bool if_initialize;

	CEES_Pthread(int iEnergyLevel =0); 
	CEES_Pthread(int, CTransitionModel *, CEES_Node *); 
	~CEES_Pthread(); 

	static void SetPthreadParameters(int ); 
	static int mutex_lock(int);
	static int mutex_unlock(int); 
	static int condition_wait(int); 
	static int condition_signal(int);  
	
	void SetHigherNodePointer(const CEES_Pthread *); 
	void Initialize(CModel *); 
	bool Initialize();	// Take a sample from previous level for initialization
	void draw(int mhM=0); 

	virtual void UpdateMinEnergy(double); 
	friend void TuneEnergyLevels_UpdateStorage(CEES_Pthread *); 
	friend void *adjust(void *); 
	void AssignSamplesGeneratedSoFar(); 
}; 

#endif
