#ifndef EQUI_ENERGY_CONSTANT
#define EQUI_ENERGY_CONST
// ****** c is to determine temperature levels based on energy levels: H[i+1]-H[i]=cT[i] ******/ 
const double C = 1.4;
const int NUMBER_ENERGY_LEVEL = 10;
const int BURN_IN_PERIOD = 10000;
const double H0 = 0;
const double HK_1 = 1000;
const double T0 = 1.0;
const double TK_1 = 100;
const int DATA_DIMENSION = 50;
const int SIMULATION_LENGTH = 100000;
const double PEE = 0.3;
const int DEPOSIT_FREQUENCY = 100;

const int MH_STEPSIZE_TUNING_MAX_TIME = 50; 
const int MH_TRACKING_LENGTH = 100; 
const double MH_TARGET_ACC = 0.3; 

const bool MH_BLOCK = true;

const int ENERGY_LEVEL_TRACKING_WINDOW_LENGTH = 10000; 
const int ENERGY_LEVEL_TUNING_MAX_TIME = 2;
const int ENERGY_TRACKING_NUMBER = 100; 

const int MULTIPLE_TRY_MH = 5; 
const double INITIAL_SIGMA = 0.1; 
#endif
