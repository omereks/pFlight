

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "minCircle.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	float threshold;
	int sizeOfPoints;
	vector<Point> vecPoints;
	Circle circleCF;
	
	int getSizeOfPoints(){
		return this->sizeOfPoints;
	}

	correlatedFeatures(string feature1, string feature2, float corrlation, Line lin_reg, float threshold,vector<Point> vecPoints, int sizeOfPoints):
	feature1(feature1), feature2(feature2), corrlation(corrlation), lin_reg(lin_reg), threshold(threshold),vecPoints(vecPoints), sizeOfPoints(sizeOfPoints){}
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
protected:
	vector<correlatedFeatures> cf;
	float CorrelationThreshold;
public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);

	virtual bool checkIfAnomaly(vector<Point> vecPointOfDetect, int i, int j);

	vector<correlatedFeatures> getNormalModel(){
		return cf;
	}

};



#endif /* SIMPLEANOMALYDETECTOR_H_ */
