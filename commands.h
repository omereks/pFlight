

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

struct commandsData{
protected:
	HybridAnomalyDetector * anomalyDetector;
	TimeSeries* tsTrainData;
	TimeSeries* tsTestData;
	vector<AnomalyReport> vecAnomalyReport;
	vector<vector<int>> vecAnomalyUpload;
public:
	commandsData(){
		this->anomalyDetector = new HybridAnomalyDetector();
	}
	void setAnomalyDetector(HybridAnomalyDetector * anomalyDetector){
		this->anomalyDetector = anomalyDetector;
	}
	HybridAnomalyDetector * getAnomalyDetector(){
		return this->anomalyDetector;
	}
	void setTsTrainData(TimeSeries* ts){
		this->tsTrainData = ts;
	}
	void setTsTrainData(TimeSeries ts){
		this->tsTrainData = new TimeSeries(ts);
	}
	TimeSeries* getTsTrainData(){
		return this->tsTrainData;
	}
	void setTsTestData(TimeSeries* ts){
		this->tsTestData = ts;
	}
	TimeSeries* getTsTestData(){
		return this->tsTestData;
	}
	void setTsTestData(TimeSeries ts){
		this->tsTestData = new TimeSeries(ts);
	}
	void setVecAnomalyReport(vector<AnomalyReport> vec){
		for (int i = 0; i < vec.size(); i++)
		{
			this->vecAnomalyReport.push_back(vec[i]);
		}
	}
	vector<AnomalyReport> getVecAnomalyReport(){
		return this->vecAnomalyReport;
	}
	vector<vector<int>> getVecAnomalyUpload(){
		return this->vecAnomalyUpload;
	}
	void addVecAnomalyUpload(vector<string> vec){
		vecAnomalyUpload.clear();
		for (int i = 0; i < vec.size(); i++)
		{
			string str(vec[i]);
    		string buf;                 // Have a buffer string
    		stringstream ss(str);       // Insert the string into a stream
    		vector<int> tokens; // Create vector to hold our words
			while (getline(ss, buf, ',')){
				int bufInt = stoi(buf);
				tokens.push_back(bufInt);
			}
			vecAnomalyUpload.push_back(tokens);
		}
	}
	vector<vector<int>> buildWindow(){
		vector<vector<int>> vecRet;
		for (int i = 0; i < vecAnomalyReport.size(); i++)
		{
			vector<int> insideVec;
			insideVec.push_back(vecAnomalyReport[i].timeStep);
			for (int j = i; j < vecAnomalyReport.size(); j++)
			{
				if (vecAnomalyReport[j].timeStep +1 != vecAnomalyReport[j+1].timeStep)
				{
					insideVec.push_back(vecAnomalyReport[j].timeStep);
					i = j;
					j = vecAnomalyReport.size();
				}
			}
			vecRet.push_back(insideVec);
		}
		delDuplicatedAnomaly(vecRet);
		return vecRet;
	}
	void delDuplicatedAnomaly(vector<vector<int>> vec){
		for (int i = 0; i < vec.size(); i++)
		{
			for (int j = 0; j < vec.size(); j++)
			{
				if (i!=j)
				{
					
					// j is inside i
					if((vec[i][0] <= vec[j][0]) && (vec[i][1] >= vec[j][1]))
					{
						vec.erase(vec.begin()+j);
						i = 0;
						j = 0;
						break;
					}

					if((vec[i][0] >= vec[j][0]) && (vec[i][1] >= vec[j][1]) && (vec[i][0] <= vec[j][1]))
					{
						vec[i][0] = vec[j][0];
						vec.erase(vec.begin()+j);
						i = 0;
						j = 0;
						break;
					}

					if((vec[i][1] <= vec[j][1]) && (vec[i][0] <= vec[j][0]) && (vec[i][1] >= vec[j][0]))
					{
						vec[i][1] = vec[j][1];
						vec.erase(vec.begin()+j);
						i = 0;
						j = 0;
						break;
					}
				}
				
			}
			
		}
		
	}
};

class DefaultIO{
public:
	DefaultIO(){};
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}
	virtual void uploadFile(string fileName) {}

	// you may add additional methods here
};

class standartIO:public DefaultIO {
public:
	standartIO():DefaultIO(){};
	virtual string read(){
		string line;
		cin>>line;
		return line;
	}
	virtual void write(string text){
		cout<<text;
	}
	virtual void write(float f){
		cout<<f;
	}
	virtual void read(float* f){
		cin>>*f;
	}
	virtual void uploadFile(string fileName) {
		ofstream filestream(fileName);
		string readLine = "";
		while (readLine != "done")
		{
			filestream<<readLine<<endl;
		}
		write("Upload complete.\n");
		filestream.close();
	}
};

//class socketIO:public DefaultIO{
//public:	
//};

// you may add here helper classes


// you may edit this class
class Command{
protected:
	commandsData * data;
	DefaultIO* dio;
	string description;
public:
	Command(DefaultIO* dio, commandsData * data):dio(dio), data(data){}
	virtual void execute()=0;
	virtual ~Command(){}
	string getDescription(){return this->description;}
	commandsData * getData(){return this->data;}
};


//Command 1 - upload a time series csv file
class CommandOneUploadFile: public Command{
	public:
		CommandOneUploadFile(DefaultIO* dio, commandsData * data):Command(dio, data){	
			this->description = "1.upload a time series csv file\r\n";
		}
		void execute(){
			this->dio->write("Please upload your local train CSV file.\r\n");
			//string uploadFilePath = this->dio->read();
			this->dio->uploadFile("traindata.csv");	
			this->getData()->setTsTrainData(TimeSeries("traindata.csv"));

			this->dio->write("Please upload your local test CSV file.\r\n");
			//string uploadFilePath = this->dio->read();
			this->dio->uploadFile("testdata.csv");
			this->getData()->setTsTestData(TimeSeries("testdata.csv"));
		}
};

//Command 2 - algorithm settings
class CommandTwoAlgorithmSettings: public Command{
	public:
		CommandTwoAlgorithmSettings(DefaultIO* dio, commandsData * data):Command(dio, data){		
			this->description = "2.algorithm settings\r\n";
		}
		void execute(){
			this->dio->write("The current correlation threshold is ");
			this->dio->write(this->getData()->getAnomalyDetector()->getCorrelationThreshold());
			this->dio->write("\r\n");
			this->dio->write("Type a new threshold\r\n");
			string newCorS = this->dio->read();
			float newCor =  stof(newCorS);
			if (newCor >= 0 && newCor <= 1)
			{
				this->data->getAnomalyDetector()->setCorrelationThreshold(newCor);
				return;
			}
			this->dio->write("please choose a value between 0 and 1.\r\n");
			this->dio->read();
			this->execute();
		}
};

//Command 3 - detect anomalies
class CommandThreeDetectAnomalies: public Command{
	public:
		CommandThreeDetectAnomalies(DefaultIO* dio, commandsData * data):Command(dio, data){	
			this->description = "3.detect anomalies\r\n";
		}
		void execute(){
			this->getData()->getAnomalyDetector()->learnNormal(*this->getData()->getTsTrainData());
			vector<AnomalyReport> vecAnomaly = this->getData()->getAnomalyDetector()->detect(*this->getData()->getTsTestData());
			this->getData()->setVecAnomalyReport(vecAnomaly);
			this->dio->write("anomaly detection complete.\r\n");
		}
};

//Command 4 - display results
class CommandFourDisplayResults: public Command{
	public:
		CommandFourDisplayResults(DefaultIO* dio, commandsData * data):Command(dio, data){	
			this->description = "4.display results\r\n";
		}
		void execute(){
			for (int i = 0; i < this->data->getVecAnomalyReport().size(); i++)
			{
				this->dio->write(this->data->getVecAnomalyReport()[i].timeStep);
				this->dio->write("\t");
				this->dio->write(this->data->getVecAnomalyReport()[i].description);
				this->dio->write("\r\n");
			}
			this->dio->write("Done.\r\n");

		}
};

//Command 5 - upload anomalies and analyze results
class CommandFiveUploadAnomalies: public Command{
	public:
		CommandFiveUploadAnomalies(DefaultIO* dio, commandsData * data):Command(dio, data){	
			this->description = "5.upload anomalies and analyze results\r\n";
		}
		void execute(){
			this->dio->write("Please upload your local anomalies file.\r\n");
			//ofstream filestream(this->dio->read());
			string readLine = "";
			vector<string> anomalyUpload;
			while (readLine != "done")
			{
				readLine = this->dio->read();
				if (readLine != "done")
				{
					anomalyUpload.push_back(readLine);
				}
			}
			this->data->addVecAnomalyUpload(anomalyUpload);
			this->dio->write("Upload complete.\r\n");

			//P
			float P = this->data->getVecAnomalyUpload().size();
			int sum = 0;
			
			//N
			for (int i = 0; i < this->data->getVecAnomalyUpload().size(); i++)
			{
				sum += this->data->getVecAnomalyUpload()[i][1] - this->data->getVecAnomalyUpload()[i][0];
			}
			float N = this->data->getTsTestData()->vecCSV.size() - sum + 1;

			//TP
			float TP = 0;
			for (int i = 0; i < this->data->getVecAnomalyUpload().size(); i++)
			{
				for (int j = 0; j < this->data->getVecAnomalyReport().size(); j++)
				{
					if (this->data->getVecAnomalyReport()[j].timeStep >=  this->data->getVecAnomalyUpload()[i][0] && this->data->getVecAnomalyReport()[j].timeStep <= this->data->getVecAnomalyUpload()[i][1])
					{
						TP++;
						j++;
						if (i + 1  < this->data->getVecAnomalyUpload().size())
						{
							i++;
						}
						else
						{
							break;
						}
					}	
				}
			}

			//FP
			float FP = 0;
			vector<vector<int>> vecWindow = this->data->buildWindow();
			for (int i = 0; i < vecWindow.size(); i++)
			{
				bool flag = false;
				for (int j = 0; j < this->data->getVecAnomalyUpload().size(); j++)
				{
					if (((vecWindow[i][0] >= this->data->getVecAnomalyUpload()[j][0]) && (vecWindow[i][0] <= this->data->getVecAnomalyUpload()[j][1])) || ((vecWindow[i][1] >= this->data->getVecAnomalyUpload()[j][0]) && (vecWindow[i][1] <= this->data->getVecAnomalyUpload()[j][1])))
					{
						flag = true;
					}
					if (((this->data->getVecAnomalyUpload()[j][0] >= vecWindow[i][0]) && (this->data->getVecAnomalyUpload()[j][0] <= vecWindow[i][1])) || ((this->data->getVecAnomalyUpload()[j][1] >= vecWindow[i][0]) && (this->data->getVecAnomalyUpload()[j][1] <= vecWindow[i][1])))
					{
						flag = true;
					}
					
				}
				if (!flag)
				{
					FP++;
				}
			}
			


			float tpRate = TP / P ;
			float fpRate = FP / N ;

			if (tpRate != 1)
			{
				tpRate = (float)(((int)(tpRate*1000)) % 1000)/1000;
			}
			if (fpRate != 1)
			{
				fpRate = (float)(((int)(fpRate*1000)) % 1000)/1000;
			}
			this->dio->write("True Positive Rate: ");
			this->dio->write(tpRate);
			this->dio->write("\r\n");

			this->dio->write("False Positive Rate: ");
			this->dio->write(fpRate);
			this->dio->write("\r\n");

		}
};

//Command 6 - exit
class CommandSixExit: public Command{
	public:
		CommandSixExit(DefaultIO* dio, commandsData * data):Command(dio, data){	
			this->description = "6.exit\r\n";
		}
		void execute(){
			this->dio->write(this->description);
		}
};



#endif /* COMMANDS_H_ */
