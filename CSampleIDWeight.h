#ifndef _CSAMPLE_ID_WEIGHT
#define _CSAMPLE_ID_WEIGHT

#include <iostream>
#include <fstream>
// #include <vector>

using namespace std; 

class CSampleIDWeight
{
private: 
	int dim; 
	//vector <double> data; 
	double *data; 
	int id; 
	double weight; 
	double if_weight_set; // true if weight has been specifically set
public: 
	CSampleIDWeight(); 
	CSampleIDWeight(const double *, int, int, double); 
	// CSampleIDWeight(const vector <double> &, int, double); 
	CSampleIDWeight(const CSampleIDWeight &); 
	~CSampleIDWeight();

	void SetDataDimension(int); 
	int GetDataDimension() const { return dim; }
	CSampleIDWeight & operator=(const CSampleIDWeight &);
	void SetID(int _id) { id = _id; } 		
	int GetID() const { return id; }
	void SetWeight(double _weight) { weight = _weight; if_weight_set = true; }
	double GetWeight() const { return weight; }
	int GetSize_Data();
	bool WeightSet () const { return if_weight_set; }

	double *GetData() { return data; }
	void GetData(double *, int, int &, double &); 
	// void GetData(vector < double > &, int &, double &);

	friend istream& read(istream &, CSampleIDWeight *); 
	friend ostream& write(ostream &, const CSampleIDWeight *);

	friend istream& operator>>(istream &, CSampleIDWeight &); 
	friend ostream& operator<<(ostream &, const CSampleIDWeight &); 
}; 

#endif
