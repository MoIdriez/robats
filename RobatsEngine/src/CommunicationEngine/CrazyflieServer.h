/*
 * CrazyflieServer.h
 *
 *  Created on: 4 May 2016
 *      Author: midries
 */

#ifndef COMMUNICATIONENGINE_CRAZYFLIESERVER_H_
#define COMMUNICATIONENGINE_CRAZYFLIESERVER_H_

#include <thread>
#include <netinet/in.h>

using namespace std;

class CrazyflieServer {
public:
	CrazyflieServer(int port, int* data);
	virtual ~CrazyflieServer();

private:
	int* data;
	int port;
	int serversocket;
	int clientsocket;
	thread mainthread;
	struct sockaddr_in serveraddress;

	void start();
	void handleClient();
};

#endif /* COMMUNICATIONENGINE_CRAZYFLIESERVER_H_ */
