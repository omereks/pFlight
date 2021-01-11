

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
	vector<AnomalyReport> * vecAnomalyReport;
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
		this->vecAnomalyReport = &vec;
	}
	vector<AnomalyReport> * getVecAnomalyReport(){
		return this->vecAnomalyReport;
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
protected:
	ifstream in;
    ofstream out;
public:
	standartIO():DefaultIO(){};
	virtual string read(){
		string line;
		cin>>line;
		return line;
	}
	virtual void write(string text){
		out<<text;
	}
	virtual void write(float f){
		out<<f;
	}
	virtual void read(float* f){
		in>>*f;
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
			this->getData()->setVecAnomalyReport(this->getData()->getAnomalyDetector()->detect(*this->getData()->getTsTestData()));
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
			this->dio->write(this->description);
		}
};

//Command 5 - upload anomalies and analyze results
class CommandFiveUploadAnomalies: public Command{
	public:
		CommandFiveUploadAnomalies(DefaultIO* dio, commandsData * data):Command(dio, data){	
			this->description = "5.upload anomalies and analyze results\r\n";
		}
		void execute(){
			this->dio->write(this->description);
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
