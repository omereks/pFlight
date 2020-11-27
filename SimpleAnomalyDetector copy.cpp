
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
	float corrlation;
	int numOfC = ts2.features.size();

	for (int i = 0; i < numOfC ; i++)
	{
		for (int j=i+1; j < numOfC; j++)
		{
			// i is the first column and j is second the column

			//make the column from vector to array

			vector<float> v = ts2.getColumn(i);
			float* arr = &v[0];
			vector<float> v2 = ts2.getColumn(j);
			float* arr2 = &v2[0];

			//check the corralation of 2 columns
			corrlation = pearson(arr , arr2 , v2.size());

			//check if the corraltion is good
			if ((corrlation>=0.9) || (corrlation<=(-0.9)))
			{
				// wants to save correlatedFeatures object and push it to this->cf
				// needs:

				//string feature1,feature2
				//float corrlation (have already - corrlation)
				//Line lin_reg
				//float threshold
				//int sizeOfPoints (have already - v.size())



				// names of the correlated features
				string feature1 = ts2.features[i];
				string feature2 = ts2.features[j];

				//making a line from all the points				
				Point * pArr[v.size()] = {};
				float maxDev = 0;

				//initaliz all point
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

				maxDev = maxDev*1.2;

				correlatedFeatures corToAdd(feature1, feature2, corrlation, lin_reg, maxDev, v.size());
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
		int indCX = ts3.foundC(this->cf[i].feature1);
		int indCY = ts3.foundC(this->cf[i].feature2);
		
		//make point for each cf
		for (int j = 0; j < this->cf[i].sizeOfPoints ; j++)
		{
			//float one = dev(*this->cf[i].arrp[j], this->cf[i].arrp, this->cf[i].sizeOfPoints);
			//from now
			
			
			float x = ts3.getVal(i,indCX);

			float one = (dev(Point(ts3.getVal(j,indCX),ts3.getVal(j,indCY)) , this->cf[i].lin_reg));
			//from learning
			float tow = this->cf[i].threshold;
			if(one  > tow)
			{
				string description = this->cf[i].feature1 + "-" + this->cf[i].feature2;
				long timeStep = j+1;
				//long timeStep = this->cf[j][0];
				vecAnomalyRet.push_back(AnomalyReport(description, timeStep));
			} 
		}
		
	}
	return vecAnomalyRet;
	// TODO Auto-generated destructor stub
}

