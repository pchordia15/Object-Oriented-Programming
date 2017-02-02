/*
	Server.h contain all the declaration of methods and members
	Server class is the class that provide the services for server to run.
*/
#include <stdlib.h>
#include <iostream>
#include <sys/socket.h>
#include <string>
#include <sys/types.h>
#include <netinet/in.h>

using namespace std;

class server
{
	private:
		int sockfd, newsockfd, portno;
		//socklen_t clilen;
		char client_msg[1048];
		struct sockaddr_in serv_add, cli_addr;
		int n;
		void error(char *message);
	public:
		server();
		server(int pno);
		~server();
		int start();
		int readData(string *client_response);
		void sendData(char msg[]);
		int stopClient();
		void stop();
		char* getIPAddress();
		char* getSystemTime();
		string getCurrentTime();
};

