#ifndef CEES_NODE
#define CEES_NODE

#include <gsl/gsl_rng.h>
#include <gsl/gsl_poly.h>
#include <cfloat>
#include <cmath>
#include "CModel.h"
#include "CTransitionModel.h"
#include "CStorageHead.h"

class CEES_Node
{
protected:
	/* class variables */
	static int K; 		// number of energy levels;
	static vector <double >H; 	// own: lower bound energy of all energy levels
	static vector <double >T; 	// own: temperature of all energy levels
	static double pee; 	// prob of equi-energy jump
	int B; 			// burn-in period might be different for different nodes
	static int N; 		// period to build initial energy set;
	static int dataDim; 	// data dimension
	static int depositFreq; 	// how often to save deposit freq

	/* block MH */
	static int nBlock; 	// number of blocks that data can be grouped in
	static vector <int> blockSize;	// size of each block

protected: 
	static vector <double> min_energy;	// record min_energy to tune energy levels. 
	static vector <double> max_energy; // recod max_energy to tune energy levels	
	static int min_max_energy_capacity; 
	/* instance variables */
protected: 
	int id;			// index of the this level;
	CEES_Node * next_level; // CEES_Node whose energy is one level above		
	int nSamplesGenerated;	// number of sampels generated at this level;

	/* adjusting MH step size */		
	int nMHSamplesGenerated_Recent;	// number of rencently generated MH samples
	vector <int> nMHSamplesAccepted_Recent;	// number of recently accepted MH samples 
	int MH_Tracking_Length; 
	bool MH_On; 	
	double MH_lower_target_prob; 
	double MH_upper_target_prob;	
	void MH_Tracking_End(); 	// Tune proposal
	
	/* current and new samples */ 
	double *x_current;	// own: current sample
	double *x_new;		// own: new sample 
	int ring_index_current; // energy ring index of current sample
	double energy_current; 	// energy of current sample
	vector <int > ring_size;

	/* target and MH proposal distributions of this level */
	CModel *target;		// own: target of this level 	
	CTransitionModel **proposal; 	// own: proposal model used at this level
	double LogProbRatio(const double *, const double *, int); 
	double OriginalEnergy(const double *x, int d) { return CEES_Node::ultimate_target->energy(x, d); }

	int GetRingIndex(double) const;
	bool BurnInDone();
	void Initialize(const gsl_rng *); 	// directly using target->draw to get the first sample
public:	
	static CModel *ultimate_target;		// access: target distribution; 

	CEES_Node(int iEngergyLevel =0); 
	CEES_Node(int, CTransitionModel *, CEES_Node *);
	CEES_Node(int, CTransitionModel **, CEES_Node *);
	~CEES_Node();
	
	void SetID_LocalTarget(int); 
	int GetID() const { return id; }
	void SetProposal (CTransitionModel *transition, int iBlock =0) { proposal[iBlock] = transition; }
	CTransitionModel *GetProposal(int iBlock =0) const { return proposal[iBlock]; }
	void SetHigherNodePointer (CEES_Node *higher) { next_level = higher; }
	int BinID(int) const; 	// determine the index of the bin given the energy
	int BinID(double ) const;	// determine the index of the bin given the ring index

	double GetEnergy() const { return CEES_Node::H[id]; }
	double GetTemperature() const { return CEES_Node::T[id]; }

	void Initialize(CModel *, const gsl_rng *); 
	void Initialize(const double *, int); 
	void draw(const gsl_rng*, CStorageHead &, int mhM=0); 	// multiple-try MH, linked with CStorageHead
	void draw_block(const gsl_rng*, CStorageHead &);		// block MH

	bool EnergyRingBuildDone() const; 
	friend ofstream & summary(ofstream &, const CEES_Node *); 
	void MH_Tracking_Start(int, double lp=0.1, double up=0.3);	// ideal acceptance rate for multi-dimensional Gaussian proposal distribution ~ 0.23 
	

	static void SetDataDimension(int); 
	static int GetDataDimension() ;
	static void SetEnergyLevelNumber(int); 
	static int GetEnergyLevelNumber() ;
	static void SetEquiEnergyJumpProb(double); 
	int GetEquiEnergyJumpProb() ; 
	void SetBurnInPeriod(int); 
	int GetBurnInPeriod() const; 
	static void SetPeriodBuildInitialRing(int); 
	static int GetPeriodBuildInitialRing() ; 
	static void SetDepositFreq(int); 
	static int GetDepositFreq();
	static void InitializeMinMaxEnergy(int); 
	virtual void UpdateMinMaxEnergy(double); 
	
	static bool SetEnergyLevels(double *, int); 
	static bool SetEnergyLevels_GeometricProgression(double, double); 

	static bool SetTemperatures(double *, int); 
	static bool SetTemperatures_EnergyLevels(double, double, double); 
	static bool SetTemperatures_EnergyLevels(double, double); 

	static void SetBlockSize(const int*, int _nB=1); 
	static int GetNumberBlocks() { return nBlock; }
	static int GetBlockSize(int i) { return blockSize[i]; }

	friend void TuneEnergyLevels_UpdateStorage(CEES_Node*, CStorageHead&); 

	/* To reset H0 and make adjustment accordingly */
protected: 
	void AdjustLocalTarget(); 	// Reset the local target distribution according to the newly set energy levels and temperatures. 
	void AssignSamplesGeneratedSoFar(CStorageHead&); 
};

#endif 
