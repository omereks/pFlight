
#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "sstream"
#include "math.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Server.h"

Server::Server(int port)throw (const char*) {
	this->serverPort = port;
	this->setFd(socket(AF_INET, SOCK_STREAM, 0));
	if (this->getFd()<0){
		throw "failed to build the socket";
	}
	this->server.sin_family = AF_INET;
	this->server.sin_addr.s_addr = INADDR_ANY;
	this->server.sin_port = htons(port);

	if(bind(this->getFd(), (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		throw "bind failed";
	}

	if(listen(this->getFd(), 2) < 0){
		throw "listen failed";
	}
}

void thredFunc(Server * s, ClientHandler& ch ) throw(const char*){
	//ch.setClientID(s->serverPort);
	socklen_t clientSize = sizeof(s->client);
	int oneClient;
	//s->setStopCondition(false);
	//while (!s->getStopCondition()){
		if (oneClient = accept(s->getFd(), (struct sockaddr*)&(s->client), &clientSize) < 0)
		{
			throw "error in acceptConnection";
		}
		ch.handle(oneClient);
		close(oneClient);
	//}
	close(s->getFd());
}

void Server::start(ClientHandler& ch) throw(const char*){
	this->t = new thread([&ch, this]() {
        socklen_t clientSize = sizeof(client);
		while (!getstopCondition()) {
            int oneClient = accept(getFd(), (struct sockaddr*)&client, &clientSize);
            if (oneClient < 0) {
                throw "error in acceptConnection";
            }
            ch.handle(oneClient);
            close(oneClient);
        }
		close(getFd());
    });
	//this->t = new thread(thredFunc, this, ref(ch));

}

void Server::stop(){
	this->stopCondition = true;
	t->join(); // do not delete this!
}

Server::~Server() {
}

