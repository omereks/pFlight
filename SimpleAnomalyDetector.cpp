
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

			if (corrlation>0.9)
			{
				string feature1 = ts2.features[i];
				string feature2 = ts2.features[j];
				
				Point * pArr[ts2.vecCSV.size()] = {};
				float maxDev = 0;
				for (int t = 0; t < ts2.vecCSV.size(); t++)
				{
					pArr[t] = new Point(arr[t], arr2[t]);
				}
				Line lin_reg = linear_reg(pArr, ts2.vecCSV.size());

				for (int k = 0; k < ts2.vecCSV.size(); k++)
				{
					float curDev = dev(*pArr[k], lin_reg);
					if (curDev > maxDev)
					{
						maxDev = curDev;
					}
				}


				correlatedFeatures corToAdd(feature1, feature2, corrlation, lin_reg, maxDev*1.1, *pArr, ts2.vecCSV.size());
				this->cf.push_back(corToAdd);
			}
			

		}
	}
	


}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	vector<AnomalyReport>  vecAnomalyRet;
	TimeSeries ts3(ts);
	//each vector
	for (int i = 0; i < this->cf.size(); i++)
	{
		//make point for each cf
		for (int j = 0; j < this->cf[i].sizeOfPoints ; j++)
		{
			if(dev(this->cf[i].arrp[j], this->cf[i].lin_reg)  > this->cf[i].corrlation)
			{
				string description = this->cf[i].feature1 + "-" + this->cf[i].feature2;
				long timeStep = ts3.getVal(j,0);
				vecAnomalyRet.push_back(AnomalyReport(description, timeStep));
			} 
		}
		
	}
	return vecAnomalyRet;
	// TODO Auto-generated destructor stub
}

