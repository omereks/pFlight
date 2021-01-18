/*
 * Server.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Eli
 */

#ifndef SERVER_H_
#define SERVER_H_
#include "commands.h"
#include "CLI.h"



using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};


// you can add helper classes here and implement on the cpp file


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
	DefaultIO* dio;
	public:
    virtual void handle(int clientID){
		this->dio = new socketIO(clientID);
		//this->dio->setClientID(clientID);
		CLI cli(this->dio);
		cli.start();
    }
};


// implement on Server.cpp
class Server {
	bool stopCondition = false;
	int fd;
public: 														//////
	thread* t; // the thread to run the start() method in
	sockaddr_in server;
	sockaddr_in client;
	int serverPort;
	// you may add data members

	Server(int port) throw (const char*);
	virtual ~Server();
	//void thredFunc(server s,ClientHandler& ch);
	void start(ClientHandler& ch)throw(const char*);
	void stop();
	
	
	int getFd(){
		return this->fd;
	}
	void setFd(int fd){
		this->fd = fd;
	}

	bool getstopCondition(){
		return this->stopCondition;
	}
	void setstopCondition(bool stopCondition){
		this->stopCondition = stopCondition;
	}

};

#endif /* SERVER_H_ */
