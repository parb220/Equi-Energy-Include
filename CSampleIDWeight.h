#ifndef _CSAMPLE_ID_WEIGHT
#define _CSAMPLE_ID_WEIGHT

#include <iostream>
#include <fstream>
// #include <vector>

using namespace std; 

class CSampleIDWeight
{
private: 
	static int dim; 
	//vector <double> data; 
	double *data; 
	int id; 
	double weight; 
public: 
	CSampleIDWeight(); 
	CSampleIDWeight(const double *, int, double); 
	// CSampleIDWeight(const vector <double> &, int, double); 
	CSampleIDWeight(const CSampleIDWeight &); 
	~CSampleIDWeight();

	static void SetDataDimension(int); 
	CSampleIDWeight & operator=(const CSampleIDWeight &);
	void SetID(int _id) { id = _id; } 		
	int GetID() const { return id; }
	void SetWeight(double _weight) { weight = _weight; }
	double GetWeight() const { return weight; }
	static int GetSize_Data();

	void GetData(double *, int, int &, double &); 
	// void GetData(vector < double > &, int &, double &);

	friend istream& read(istream &, CSampleIDWeight *); 
	friend ostream& write(ostream &, const CSampleIDWeight *);
}; 

#endif
