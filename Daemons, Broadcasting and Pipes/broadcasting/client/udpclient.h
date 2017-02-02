// DESCRIPTION
// This file contains the client class and it will be used during the execution in main.cpp.
// Besides constructors, the member functions of client class are: connect_to_server, receive, 
//send , getBuff and clearBuff.
//
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER "127.255.255.255"
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to send data

class udpclient
{
	private:
		int sockfd;
		struct sockaddr_in si_other;
		char buf[BUFLEN];
	public:
		udpclient();
		~udpclient();
		int connect_to_server();
		int send(char *message);
		int receive();
		void error(char *message);
		char* getBuf();
		void clearBuf();
		
};
