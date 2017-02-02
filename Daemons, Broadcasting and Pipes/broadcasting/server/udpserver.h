/*
udpserver.h contain all the declaration of methods and members
udpsServer class is the class that provide the services for server to run.
*/
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFLEN 512  //Max length of buffer
#define PORT 8888
class udpserver
{
	private:
		struct sockaddr_in si_me, si_other;
		int sockfd;
    	char buf[BUFLEN];

	public:
		udpserver();
		~udpserver();
		int start();
		int send(char *message);
		int receive();
		void error(char *error_message);
		char* getBuf();
		void clearBuf();
};
