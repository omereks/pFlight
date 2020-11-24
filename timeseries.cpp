#include "timeseries.h"


void TimeSeries::creatVectorFromCSV(const char* CSVfileName){
    vector<vector<float>> vecrCSV;
    ifstream  csv;
    bool flag = true;
    csv.open(CSVfileName);
    string strLine, val;
    while (getline(csv, strLine))
    {
        vector<float> vecLine;
        stringstream s(strLine);
        if(flag)
        {
            while (getline(s, val, ','))
            {
                this->features.push_back(val);
            }
            flag = false;
        }
        else
        {
            while (getline(s, val, ','))
            {
                vecLine.push_back(stof (val));
            }
            this->vecCSV.push_back(vecLine);
        }
    }
}


float TimeSeries::getVal(int r, int c){
    return (this->vecCSV[r][c]);
}

vector<float> TimeSeries::getRow(int r){
    return (this->vecCSV[r]);
}

void TimeSeries::getColumn(float* arrC, int c){
    vector<float> curVec;
    float curVal;
    int i = 0;
    for (int i = 0 ; i < this->vecCSV.size() ; i++)
    {
        arrC[i] = this->vecCSV[i][c];
    }
}

void TimeSeries::addRow(float a, float b, float c, float d){
    vector<float> vecAdd;
    vecAdd.push_back(a);
    vecAdd.push_back(b);
    vecAdd.push_back(c);
    vecAdd.push_back(d);

    this->vecCSV.push_back(vecAdd);
}







