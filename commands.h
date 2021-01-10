

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

	// you may add additional methods here
};

class standartIO:public DefaultIO {
public:
	virtual string read(){
		string line;
		cin>>line;
		return line;
	}
	virtual void write(string text){
		cout<<text;
	}
	virtual void write(float f){
		cout<<f<<endl;
	}
	virtual void read(float* f){
		cin>>*f;
	}
};

//class socketIO:public DefaultIO{
//public:	
//};

// you may add here helper classes


// you may edit this class
class Command{
protected:
	DefaultIO* dio;
	string description;
public:
	Command(DefaultIO* dio):dio(dio){}
	virtual void execute()=0;
	virtual ~Command(){}
	string getDescription(){return this->description;}
};


//Command 1 - upload a time series csv file
class CommandOneUploadFile: public Command{
	public:
		CommandOneUploadFile(DefaultIO* dio):Command(dio){	
			this->description = "1.upload a time series csv file\r\n";
		}
		void execute(){
			this->dio->write(this->description);
		}
};

//Command 2 - algorithm settings
class CommandTwoAlgorithmSettings: public Command{
	public:
		CommandTwoAlgorithmSettings(DefaultIO* dio):Command(dio){	
			this->description = "2.algorithm settings\r\n";
		}
		void execute(){
			this->dio->write(this->description);
		}
};

//Command 3 - detect anomalies
class CommandThreeDetectAnomalies: public Command{
	public:
		CommandThreeDetectAnomalies(DefaultIO* dio):Command(dio){	
			this->description = "3.detect anomalies\r\n";
		}
		void execute(){
			this->dio->write(this->description);
		}
};

//Command 4 - display results
class CommandFourDisplayResults: public Command{
	public:
		CommandFourDisplayResults(DefaultIO* dio):Command(dio){	
			this->description = "4.display results\r\n";
		}
		void execute(){
			this->dio->write(this->description);
		}
};

//Command 5 - upload anomalies and analyze results
class CommandFiveUploadAnomalies: public Command{
	public:
		CommandFiveUploadAnomalies(DefaultIO* dio):Command(dio){	
			this->description = "5.upload anomalies and analyze results\r\n";
		}
		void execute(){
			this->dio->write(this->description);
		}
};

//Command 6 - exit
class CommandSixExit: public Command{
	public:
		CommandSixExit(DefaultIO* dio):Command(dio){	
			this->description = "6.exit\r\n";
		}
		void execute(){
			this->dio->write(this->description);
		}
};



#endif /* COMMANDS_H_ */
