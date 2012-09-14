#ifndef _C_PARAMETER_PACKAGE
#define _C_PARAMETER_PACKAGE

#include <gsl/gsl_rng.h>
#include <string>
#include <vector>
#include "CSampleIDWeight.h"

using namespace std; 

class CStorageHead; 
class CEES_Node; 

class CParameterPackage
{
public:
	// The following parameter can either be determined from reading the file or command line or by default values (specified in a header file)
	 int number_cluster_node; 
	 int run_id; 
	 int get_marker;		// number of samples stored in memory for retrieve 
	 int put_marker; 	// number of samples stored in memory before dumping to hard-drive
	 int number_energy_level;	// number of energy levels
	 int data_dimension; 	// dimension of samples
	 int number_bins;	// total number of bins in storage = number_energy_level * number_energy_level
	 double pee; 	// probability of equi-energy-jump
	 double h0; 	// energy bound for the lowest energy level
	 double hk_1; 	// energy bound for the highest energy level
	 int energy_tracking_number;	// number of min and max energies to track for tuning h0 and/or hk_1
	 double t0; 	// temperature for the lowest energy level
	 double c_factor;	// C factor to determine temperatures based on energy bounds, (H[i]-H[i-1])/(T[i]-T[i-1])=C
	 double mh_target_acc; 	// target acceptance rate to tune the sales of the proposal distribution for MH
	 double initial_sigma; 	// initial sigma of the proposal distribution 
	 double uniform_lb; 	// lower bound of uniform distribution to initialize the sampler
	 double uniform_ub; 	// upper bound of uniform distribution to initialize the smapler
	 int burn_in_period; 
	 int multiple_try_mh; 	// number of MH tries for multiple-try-MH
	 int mh_tracking_length; 	// tracking length during mh scale tuning
	 int mh_stepsize_tuning_max_time; // number of tracking periods during mh scale tuning
	 int energy_level_tracking_window_length;	// tracking length before tuning H0 and HK-1
	 int energy_level_tuning_max_time; 	// number of tracking periods for tuning H0 and HK-1
	 int deposit_frequency; 	// frequency of depositing samples
	 int simulation_length;	// length of simulation 
	 int number_block;	// number of blocks  

private:
	// The following parameters can only be set after at least one run of simulation
	vector <vector <double> > scale; 	// scale of MH proposal distribution
	// vector <int> number_samples_generated_by_far; 	// nSamplesGeneratedByFar for each bin
	vector <int> number_files_fetch; 
	vector <CSampleIDWeight> x_current;	// last samples
	// vector <int> energy_index_current;	// energy index of last samples
	vector <double> h, t; 	// energy-bound and temperature for all levels
	vector <int> block_size; 	// size of each block
public:
	CParameterPackage(); 
	~CParameterPackage(); 
	bool LoadParameterFromFile(string); 
	bool LoadCurrentStateFromFile(string); 
	void TraceStorageHead(const CStorageHead &); 	
	void TraceSimulator(const CEES_Node &); 
	bool SaveParameterToFile(string) const;
	bool SaveCurrentStateToFile(string) const; 
	bool WriteSummaryFile(string) const; 
	
	void SetBlock(int * = NULL); 
	bool SetEnergyBound();
	bool SetTemperature();
	bool SetMHProposalScale();
	void SetCurrentState(const gsl_rng *); 

	// int EnergyIndexLastSample(int id) const { return energy_index_current[id]; }
	void GetMHProposalScale (int id, double *, int) const;  
	vector <double > GetMHProposalScale(int id) const { return scale[id]; }
	// int NumberSamplesGeneratedByFar(int id) const { return number_samples_generated_by_far[id]; } 
	CSampleIDWeight GetCurrentState(int id) const { return x_current[id]; } 
	// int GetCurrentEnergyIndex(int id) const { return energy_index_current[id]; }
	void GetEnergyBound(double *, int) const; 
	void GetTemperature(double *, int) const; 
	void GetBlockSize(int *, int) const; 
	int GetBlockSize(int _id) const { return block_size[_id]; }
};
#endif
