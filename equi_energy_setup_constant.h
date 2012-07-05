#ifndef EQUI_ENERGY_CONSTANT
#define EQUI_ENERGY_CONST
// ****** c is to determine temperature levels based on energy levels: H[i+1]-H[i]=cT[i] ******/ 
const double C = 1.4;
const int NUMBER_ENERGY_LEVEL = 5;
const int BURN_IN_PERIOD = 5000;
const int BUILD_INITIAL_ENERGY_SET_PERIOD = 50000;
const double H0 = 10.0;
const double HK_1 = 100;
const double T0 = 1.0;
const double TK_1 = 60.0;
const int DATA_DIMENSION = 2;
const int SIMULATION_LENGTH = 10000000;
const double PEE = 0.2;
const int DEPOSIT_FREQUENCY = 100;
const int MH_TRACKING_FREQUENCY = 50000; 
const int MH_TRACKING_LENGTH = 1000; 
const int ENERGY_LEVEL_TUNING_FREQUENCY = 5000000; 
const int ENERGY_LEVEL_TUNING_MAX_TIME = 2;
#endif
