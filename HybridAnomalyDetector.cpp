
#include "HybridAnomalyDetector.h"
#include <iostream>

HybridAnomalyDetector::HybridAnomalyDetector() {
	// TODO Auto-generated constructor stub
	CorrelationThreshold = 0.9;
}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

bool HybridAnomalyDetector::checkIfAnomaly(vector<Point> vecPointOfDetect, int i, int j){
	if (this->cf[i].corrlation >= CorrelationThreshold)
	{
		return SimpleAnomalyDetector::checkIfAnomaly(vecPointOfDetect, i, j);
	}
	if (this->cf[i].corrlation >= 0.5)
	{
		this->cf[i].circleCF = minidisc(vecPointOfDetect, { }, vecPointOfDetect.size());
		this->cf[i].circleCF.setRadius(this->cf[i].circleCF.getRadius()* 1.1 );

		if (!ifPointIsInCircle(this->cf[i].circleCF, vecPointOfDetect))
		{
			return true;
		}
		return false;
		
	}
	return true;
}
