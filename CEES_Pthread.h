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
	// static pthread_mutex_t global_mutex; 
	static vector <bool> flag; 
public: 	
	const gsl_rng *r; 
	static CStorageHeadPthread *storage;
	int burnInL; 
	int MHInitialL, MHMaxTime;
	int mMH; 
	int simulationL;
	int depositFreq;  
	vector <double> MHProposalScale;	// own

	CEES_Pthread(int iEnergyLevel =0); 
	CEES_Pthread(int, CTransitionModel *, CEES_Node *); 
	~CEES_Pthread(); 

	static void SetPthreadParameters(int ); 
	static int mutex_lock(int);
	static int mutex_unlock(int); 
	static int condition_wait(int); 
	static int condition_signal(int);  
	static void flag_turn(int _i, bool _f) { flag[_i] = _f; }
	static bool flag_status(int _i) { return flag[_i]; }
	
	void SetHigherNodePointer(const CEES_Pthread *); 
	using CEES_Node::Initialize; 
	void Initialize(CModel *); 
	bool Initialize();	// Take a sample from previous level for initialization
	void draw(); 
	void BurnIn(); 
	void MH_StepSize_Regression(); 
	void MH_StepSize_Tune(); 
	void Simulate(); 

	virtual void UpdateMinMaxEnergy(double); 
	friend bool TuneEnergyLevels_UpdateStorage(CEES_Pthread *, double, double); 
	friend void *adjust(void *); 
	friend void *adjust_clear(void *); 
	void AssignSamplesGeneratedSoFar(); 
	void DisregardHistorySamples(); 
}; 

#endif
