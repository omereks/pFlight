

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
	
public:
	HybridAnomalyDetector* anomalyDetector;
	TimeSeries* tsTrainData;
	TimeSeries* tsTestData;
	void setAnomalyDetector(HybridAnomalyDetector* anomalyDetector){
		this->anomalyDetector = anomalyDetector;
	}
	HybridAnomalyDetector* getAnomalyDetector(){
		return this->anomalyDetector;
	}
	void setTsTrainData(TimeSeries* ts){
		this->tsTrainData = ts;
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
	commandsData* data;
	DefaultIO* dio;
	string description;
public:
	Command(DefaultIO* dio, commandsData* data):dio(dio){}
	virtual void execute()=0;
	virtual ~Command(){}
	string getDescription(){return this->description;}
};


//Command 1 - upload a time series csv file
class CommandOneUploadFile: public Command{
	public:
		CommandOneUploadFile(DefaultIO* dio, commandsData* data):Command(dio, data){	
			this->description = "1.upload a time series csv file\r\n";
		}
		void execute(){
			this->dio->write("Please upload your local train CSV file.\r\n");
			//string uploadFilePath = this->dio->read();
			this->dio->uploadFile("traindata.csv");
			TimeSeries* trainTS = new TimeSeries("traindata.csv");
			//TimeSeries* ptrTs = &trainTS;
			this->data->setTsTestData(trainTS);

			this->dio->write("Please upload your local test CSV file.\r\n");
			//string uploadFilePath = this->dio->read();
			this->dio->uploadFile("testndata.csv");
		}
};

//Command 2 - algorithm settings
class CommandTwoAlgorithmSettings: public Command{
	public:
		CommandTwoAlgorithmSettings(DefaultIO* dio, commandsData* data):Command(dio, data){		
			this->description = "2.algorithm settings\r\n";
		}
		void execute(){
			this->dio->write("The current correlation threshold is ");
			//this->dio->write(this->);
		}
};

//Command 3 - detect anomalies
class CommandThreeDetectAnomalies: public Command{
	public:
		CommandThreeDetectAnomalies(DefaultIO* dio, commandsData* data):Command(dio, data){	
			this->description = "3.detect anomalies\r\n";
		}
		void execute(){
			this->dio->write(this->description);
		}
};

//Command 4 - display results
class CommandFourDisplayResults: public Command{
	public:
		CommandFourDisplayResults(DefaultIO* dio, commandsData* data):Command(dio, data){	
			this->description = "4.display results\r\n";
		}
		void execute(){
			this->dio->write(this->description);
		}
};

//Command 5 - upload anomalies and analyze results
class CommandFiveUploadAnomalies: public Command{
	public:
		CommandFiveUploadAnomalies(DefaultIO* dio, commandsData* data):Command(dio, data){	
			this->description = "5.upload anomalies and analyze results\r\n";
		}
		void execute(){
			this->dio->write(this->description);
		}
};

//Command 6 - exit
class CommandSixExit: public Command{
	public:
		CommandSixExit(DefaultIO* dio, commandsData* data):Command(dio, data){	
			this->description = "6.exit\r\n";
		}
		void execute(){
			this->dio->write(this->description);
		}
};



#endif /* COMMANDS_H_ */
