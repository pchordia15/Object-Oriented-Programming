/*
DaytimeServer.h contain all the declaration of methods and members
DaytimeServer class is the class that provide the services for server to run.
*/
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

class DaytimeServer
{
	private:
	int sockfd, newsockfd, portno;
	char client_msg[1048];
	struct sockaddr_in serv_add, cli_addr;
	int n;
	void error(string message);	

	public:
	DaytimeServer();
	DaytimeServer(int pno);
	~DaytimeServer();
	int start();
	int acceptConnection();
	int readData(string *client_response);
	void sendData(char msg[]);
	string getCurrentTime();
	void closeClientSocket();
};
