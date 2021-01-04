
#include "SimpleAnomalyDetector.h"
#include "timeseries.h"
#include "anomaly_detection_util.h"
#include <iostream>


SimpleAnomalyDetector::SimpleAnomalyDetector() {
	CorrelationThreshold = 0.9;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
	TimeSeries ts2(ts);
	float corrlation;
	int numOfC = ts2.features.size();
	
	string feature1;
	string feature2;
	vector<Point>  pointsVec;
	Line lin_reg;
	Circle circ;
	float maxDev = 0;


	for (int i = 0; i < numOfC ; i++)
	{
		bool flagFoundCor = false;
		bool flagFoundCorCircle = false;
		int iCor = -1;
		int jCor = -1;
		float CorMax = 0;

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

			
			if ((corrlation > this->CorrelationThreshold) || (corrlation<((-1)*this->CorrelationThreshold)))
			{
				if (CorMax<corrlation)
				{
					flagFoundCor = true;
					iCor = i;
					jCor = j;
					feature1 = ts2.features[i];
					feature2 = ts2.features[j];
					CorMax = corrlation;
					
					//making a line from all the points	and make it an array			
					pointsVec.clear();
					for (int p = 0; p < v.size(); p++)
					{
						Point pCor(arr[p], arr2[p]);
						pointsVec.push_back(pCor);
					}
					//creat the line
					lin_reg = linear_reg(pointsVec);


					maxDev = 0;
					for (int k = 0; k < pointsVec.size(); k++)
					{
						float curDev = dev(pointsVec[k], lin_reg);
						if (curDev > maxDev)
						{
							maxDev = curDev;
						}
					}
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
				

				
			}
			if ((corrlation < this->CorrelationThreshold) && (corrlation >= 0.5))
			{
				if (CorMax<corrlation)
				{
					flagFoundCorCircle = true;
					iCor = i;
					jCor = j;
					feature1 = ts2.features[i];
					feature2 = ts2.features[j];
					CorMax = corrlation;
					
					//making a line from all the points	and make it an array			
					pointsVec.clear();
					for (int p = 0; p < v.size(); p++)
					{
						Point pCor(arr[p], arr2[p]);
						pointsVec.push_back(pCor);
					}
					circ = minidisc(pointsVec, { }, pointsVec.size());
					circ.setRadius(this->cf[i].circleCF.getRadius()* 1.1 );
					
					lin_reg = linear_reg(pointsVec);


					maxDev = 0;
					for (int k = 0; k < pointsVec.size(); k++)
					{
						float curDev = dev(pointsVec[k], lin_reg);
						if (curDev > maxDev)
						{
							maxDev = curDev;
						}
					}
				}
			}

		}
		if(flagFoundCor){
			correlatedFeatures corToAdd(feature1, feature2, CorMax, lin_reg, maxDev, pointsVec, numOfC);
			this->cf.push_back(corToAdd);
			flagFoundCor = false;
		}
		if(flagFoundCorCircle){
			correlatedFeatures corToAdd(feature1, feature2, CorMax, lin_reg, maxDev, pointsVec, numOfC, circ);
			this->cf.push_back(corToAdd);
			flagFoundCor = false;
		}
	}
	


}

bool SimpleAnomalyDetector::checkIfAnomaly(vector<Point> vecPointOfDetect, int i, int j){
	//getting one = dev from point to our line
	float one = (dev(vecPointOfDetect[j], this->cf[i].lin_reg));
	//from learning
	float tow = this->cf[i].threshold;
	tow = tow * 1.2;
	if(one  > tow)
	{
		return true;
	}
	return false;
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
			
			if(checkIfAnomaly(vecPointOfDetect, i , j))
			{
				string description = this->cf[i].feature1 + "-" + this->cf[i].feature2;
				long timeStep = j+1;
	
				vecAnomalyRet.push_back(AnomalyReport(description, timeStep));
			} 
		}
		
	}
	return vecAnomalyRet;
}

