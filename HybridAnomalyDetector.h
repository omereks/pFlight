

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
	
	virtual bool checkIfAnomaly(vector<Point> vecPointOfDetect, int i, int j) override;

	

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
