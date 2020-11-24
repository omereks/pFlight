

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
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

	float getVal(int r, int c);

    vector<float> getRow(int r);

    void getColumn(float* arrC, int c);

    void addRow(float a, float b, float c, float d);

};



#endif /* TIMESERIES_H_ */
