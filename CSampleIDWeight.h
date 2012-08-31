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

public:	// The following three variables are used for draw samples
	double log_prob; 
public: 
	CSampleIDWeight(); 
	CSampleIDWeight(const double *, int, int =0, double =0.0); 
	// CSampleIDWeight(const vector <double> &, int, double); 
	CSampleIDWeight(const CSampleIDWeight &); 
	~CSampleIDWeight();

	void SetDataDimension(int); 
	int GetDataDimension() const { return dim; }

	CSampleIDWeight & operator=(const CSampleIDWeight &);
	CSampleIDWeight operator+(const CSampleIDWeight &); 
	CSampleIDWeight operator-(const CSampleIDWeight &); 
	void PartialCopyFrom(const CSampleIDWeight &, int offset, int length);
	void PartialCopyFrom(int offset1, const CSampleIDWeight &, int offset2, int length);

	void SetID(int _id) { id = _id; } 		
	int GetID() const { return id; }

	void SetWeight(double _weight) { weight = _weight; }
	double GetWeight() const { return weight; }

	int GetSize_Data() const; 

	double *GetData() { return data; }
	double & GetData(int i) { return data[i]; }
	double & operator [](int i) { return data[i]; }
	void CopyData(double *, int, int &, double &) const;
	void CopyData(double *, int) const;  
	// void GetData(vector < double > &, int &, double &);

	friend istream& read(istream &, CSampleIDWeight *); 
	friend ostream& write(ostream &, const CSampleIDWeight *);

	friend istream& operator>>(istream &, CSampleIDWeight &); 
	friend ostream& operator<<(ostream &, const CSampleIDWeight &); 
}; 

#endif
