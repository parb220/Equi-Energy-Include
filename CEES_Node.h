#ifndef CEES_NODE
#define CEES_NODE

#include <gsl/gsl_rng.h>
#include <gsl/gsl_poly.h>
#include <cfloat>
#include <cmath>
#include "CModel.h"
#include "CTransitionModel.h"
#include "CParameterPackage.h"

class CStorageHead; 

class CEES_Node
{
/* class variables: K, H, T, pee, dataDim */
protected:
	static int K; 		// number of energy levels;
	static vector <double >H; 	// own: lower bound energy of all energy levels
	static vector <double >T; 	// own: temperature of all energy levels
	static double pee; 	// prob of equi-energy jump
	static int dataDim; 	// data dimension
	static vector <double >targetAcc; 	// own: target acceptance rate for each level's MH

public:
	static void SetDataDimension(int _d) { dataDim = _d; }
	static int GetDataDimension() { return dataDim; }
	
	static void SetEnergyLevelNumber(int _k) { K = _k; } 
	static int GetEnergyLevelNumber() { return K; }
	
	static void SetEquiEnergyJumpProb(double _p) { pee = _p; } 
	int GetEquiEnergyJumpProb() { return pee; }
	
	static bool SetEnergyLevels(double *, int); 

	static bool SetTemperatures(double *, int); 

	static bool SetTargetAcceptanceRate(double); 
	
/* class variables: block MH */
protected:
	static int nBlock; 	// number of blocks that data can be grouped in
	static vector <int> blockSize;	// size of each block

public:	
	static void SetBlockSize(const int*, int _nB=1); 
	static int GetNumberBlocks() { return nBlock; }
	static int GetBlockSize(int i=0) { return blockSize[i]; }
	
/* class variables: regarding tuning energy levels */
protected:
	vector <double> min_energy;	// record min_energy to tune energy levels. 
	vector <double> max_energy; // recod max_energy to tune energy levels
	static int min_max_energy_capacity;	// max size of the above two vectors 
	virtual void UpdateMinMaxEnergy(double); // Only MH draw will update MinMaxEnergy, because EE_draw will render a sample that is previously checked

public:
	static void InitializeMinMaxEnergy(int capacity) { min_max_energy_capacity = capacity; } 

protected: 
	int id;			// index of the this level;
	CEES_Node * next_level; // CEES_Node whose energy is one level above		
	int nSamplesGenerated;	// number of sampels generated at this level;
	
	/* current and new samples */ 
	double *x_current;	// own: current sample
	double *x_new;		// own: new sample 
	int ring_index_current; // energy ring index of current sample
	double energy_current; 	// energy of current sample
	double log_prob_current; 	// own: log_prob of current_sample
	vector <int > ring_size;	// size of the rings at this level

	int GetRingIndex(double) const;	// determine at which energy level of the given energy value
	int BinID(int energy_index) const { return id*K+energy_index; } 	// determine the index of the bin in storage given the ring index
	int BinID(double ) const;	// determine the index of the bin in storage given the energy
	
	/* target and MH proposal distributions of this level */
	CModel *target;		// own: target of this level 	
	CTransitionModel **proposal; 	// own: proposal model used at this level
	void AdjustLocalTarget(); 	// Reset the local target distribution according to the newly set energy levels and temperatures. 

	/* Draw samples */
	double LogProbRatio(const double *x, const double *y, int dim) { return target->log_prob(x, dim)-target->log_prob(y, dim); }	// log prob(x) - log prob(y)
	double LogProbRatio_Energy(double energy_x, double energy_y); 
	double OriginalEnergy(const double *x, int d) { return ultimate_target->energy(x, d); }		// energy of the ultimate_target

	bool MH_draw(const gsl_rng *, int mMH=0);	//MH draw
	// random number generator, number of MH tries
	// true for new sample 
	bool EE_draw(const gsl_rng *, CStorageHead &);	// equal-energy draw 
	// random number generator, storage where all levels of samples are stored
	// true if a sample from the higher level is accepted 
	bool draw(const gsl_rng *, CStorageHead &, int mMH=0); // Combines MH and EE draw
	// random number generator, storage where all levels of samples are stored, number of MH tries
	// true for new sample
	
public:	
	static CModel *ultimate_target;		// access: target distribution; 

	// construct and destruct
	CEES_Node(int =0, CTransitionModel * =NULL, CEES_Node * =NULL);
	CEES_Node(int, CTransitionModel **, CEES_Node * =NULL);
	~CEES_Node();

	// id	
	void SetID_LocalTarget(int); 	// also sets the local target distribution
	int GetID() const { return id; }
	CEES_Node * GetNextLevel() const { return next_level; }

	// proposal 
	void SetProposal (CTransitionModel *transition, int iBlock =0) { proposal[iBlock] = transition; }
	CTransitionModel *GetProposal(int iBlock =0) const { return proposal[iBlock]; }
	
	// higher level
	void SetHigherNodePointer (CEES_Node *higher) { next_level = higher; } 

	// energy and temperature of this level
	double GetEnergy() const { return CEES_Node::H[id]; }
	double GetTemperature() const { return CEES_Node::T[id]; }

	// Initialization	
	void Initialize(const gsl_rng *, CModel * =NULL); // use a random distribution model to get the first sample; if CModel * == NULL, directly use target->draw to get the first sample
	void Initialize(const double *, int); // use a vector for initialization
	bool Initialize(CStorageHead &, const gsl_rng *); 	// use a sample from the higher level for initialization

	// Burn-In  	
	void BurnIn(const gsl_rng *, CStorageHead &, int B, int mMH=0); 
	// random number generator, storage where all levels of samples are stored, burn-in period, number of MH tries

	// Simulation
	void Simulate(const gsl_rng *, CStorageHead &, int, int depositFreq=1, int mMH=0); 
	// random number generator, storage where all levels of samples are stored, simulation length, frequency of deposit, number of MH tries	
	
	// Tune MH stepsize
	void MH_StepSize_Tune(int, int, const gsl_rng *, int mMH=0); 	// Tune MH stepsize
	void MH_StepSize_Regression(int, int, const gsl_rng*, int mMH=0); // Estimate MH stepsize based on regression 

	// initialPeriodLength, periodNumber, targetProbability, random number generator
	friend bool TuneEnergyLevels_UpdateStorage(CEES_Node*, CStorageHead&, CParameterPackage &); 
	friend void CParameterPackage::TraceSimulator(const CEES_Node &); 

protected: 
	void AssignSamplesGeneratedSoFar(CStorageHead&); 
	void DisregardHistorySamples(CStorageHead &); 
};

#endif 
