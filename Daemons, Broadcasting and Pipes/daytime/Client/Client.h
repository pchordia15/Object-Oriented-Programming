// DESCRIPTION
// This file contains the client class and it will be used during the execution in clientMain.cpp.
// Besides constructors, the member functions of client class are: connect_to_server, receiveMessage, 
//sendMessage, getIPAddress, getPortNo, getServerReply, stop_client, getCurrentTime and readDirectory.
//

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

class client
{
	private:
		string host;
		int portno;
		
		int sock;
		struct sockaddr_in server;
		char server_reply[1024];
		
	public:
		client();
		client(string hostname, int pno);
		~client();
		
		int connect_to_server();
		int sendMessage(char msg[]);
		int receiveMessage();	
		void stop_client();
		char* getServerReply();
};
