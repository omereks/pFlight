
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
		bool flagFoundCor = false;
		int iCor = -1;
		int jCor = -1;
		int CorMax = 0;

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
			if ((corrlation>0.9) || (corrlation<(-0.9)))
			{
				if (CorMax<corrlation)
				{
					flagFoundCor = true;
					iCor = i;
					jCor = j;
				}
				
				
				
				// wants to save correlatedFeatures object and push it to this->cf
				// needs:

				//string feature1,feature2
				//float corrlation (have already - corrlation)
				//Line lin_reg
				//float threshold
				//vector<points> vecPoints
				//int sizeOfPoints (have already - v.size())



				// names of the correlated features
				string feature1 = ts2.features[i];
				string feature2 = ts2.features[j];

				//making a line from all the points	and make it an array			
				vector<Point>  pointsVec;
				for (int p = 0; p < v.size(); p++)
				{
					Point pCor(arr[p], arr2[p]);
					pointsVec.push_back(pCor);
				}
				
				//creat the line
				Line lin_reg = linear_reg(pointsVec);

				
				float maxDev = 0;
				for (int k = 0; k < pointsVec.size(); k++)
				{
					float curDev = dev(pointsVec[k], lin_reg);
					if (curDev > maxDev)
					{
						maxDev = curDev;
					}
				}

				maxDev;

				correlatedFeatures corToAdd(feature1, feature2, corrlation, lin_reg, maxDev, pointsVec, v.size());
				this->cf.push_back(corToAdd);
			}
			

		}
	}
	


}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	vector<AnomalyReport>  vecAnomalyRet;
	
	//Linr is in this->cf[i].lin_reg;
	
	TimeSeries ts3(ts);

	//each cf[i] - corrlation found
	for (int i = 0; i < this->cf.size(); i++)
	{
		//get the column numbers of X and Y
		int indCX = ts3.foundC(this->cf[i].feature1);
		vector<float> v = ts3.getColumn(indCX);
		float* arr = &v[0];
		int indCY = ts3.foundC(this->cf[i].feature2);
		vector<float> v2 = ts3.getColumn(indCY);
		float* arr2 = &v2[0];
		
		vector<Point> vecPointOfDetect;
		for (int p = 0; p < v.size(); p++)
		{
			Point pCor(arr[p], arr2[p]);
			vecPointOfDetect.push_back(pCor);
		}
		
		
		
		//check every points dec
		for (int j = 0; j < vecPointOfDetect.size() ; j++)
		{			
			//getting one = dev from point to our line
			float one = (dev(vecPointOfDetect[j], this->cf[i].lin_reg));
			//from learning
			float tow = this->cf[i].threshold;
			tow = tow * 1.2;
			if(one  > tow)
			{
				string description = this->cf[i].feature1 + "-" + this->cf[i].feature2;
				long timeStep = j+1;
	
				vecAnomalyRet.push_back(AnomalyReport(description, timeStep));
			} 
		}
		
	}
	return vecAnomalyRet;
	// TODO Auto-generated destructor stub
}

