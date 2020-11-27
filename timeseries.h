

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class TimeSeries{




public:
	string fileName;
    vector<vector<float>> vecCSV;
    vector<string> features;

	void creatVectorFromCSV(const char* CSVfileName);

	TimeSeries(const char* CSVfileName) : fileName(CSVfileName){
        this->creatVectorFromCSV(CSVfileName);
	}
	TimeSeries(const TimeSeries &ts2) {
		fileName = ts2.fileName;
		features = ts2.features;
		vecCSV = ts2.vecCSV;
	} 
	float getVal(int r, int c);

    vector<float> getRow(int r);

	int foundC(string s);

    vector<float> getColumn(int c);

    void addRow(float a, float b, float c, float d);

};



#endif /* TIMESERIES_H_ */
