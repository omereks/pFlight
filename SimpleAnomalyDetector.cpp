
#include "SimpleAnomalyDetector.h"
#include "timeseries.h"
#include "anomaly_detection_util.h"


SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
	TimeSeries ts2(ts);
	int numOfC = ts2.features.size();

	float arr[ts2.vecCSV.size()];
	float arr2[ts2.vecCSV.size()];

	float corrlation;

	float threshold = 0.9;

	for (int i = 0; i < numOfC ; i++)
	{
		for (int j=i+1; j < numOfC; j++)
		{
			ts2.getColumn(arr, i);
			ts2.getColumn(arr2, j);

			corrlation = pearson(arr,arr2,ts.vecCSV.size());

			if (corrlation>threshold)
			{
				string feature1 = ts2.features[i];
				string feature2 = ts2.features[j];
				
				Point * pArr[ts2.vecCSV.size()];
				for (int k = 0; k < ts2.vecCSV.size(); k++)
				{
					pArr[k]->setX(arr[k]);
					pArr[k]->setY(arr2[k]);

				}
				Line lin_reg = linear_reg(pArr, ts2.vecCSV.size());

				
				correlatedFeatures corToAdd(feature1, feature2, corrlation, lin_reg, threshold);
				this->cf.push_back(corToAdd);
			}
			

		}
	}
	


}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
}

