/*
udpserver.cpp files contains all the definition for server class.
udpserver class is the class that provide the services for server to run.
*/
#include "udpserver.h"
#include <iostream>
#include <string>
#include <strings.h>
#include <string.h>
#include <stdio.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
//Default constructor
udpserver :: udpserver()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Default destructor
udpserver :: ~udpserver()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// function to display error message
// input : pointer of char containing message
// output : none
void udpserver :: error(char *error_message)
{
	perror(error_message);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Function that starts the server
// input : none
// output : integer value that shows the status of with which server exited.
int udpserver :: start()
{
	cout << "Starting Server UDP server..." << endl;
	
	cout << "\tCreating socket....";
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if(sockfd == -1)
	{
		cout << "[failed]" << endl;
		error((char *)"Socket");
		return -1;
	}
	cout << "[success]" << endl;
	
	bzero(&si_me, sizeof(si_me));
	
	si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

	cout << "\tBinding server to a address and port...." << endl;	
	int bind_val = bind(sockfd , (struct sockaddr*)&si_me, sizeof(si_me));

	if(bind_val == -1)
	{
		cout << "[failed]" << endl;
		error((char *)"Bind");
		return -1;
	}
	cout << "[success]" << endl;
	cout << "Server started." << endl;
	cout << "Waiting for connections...";

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// function to send data to client
// input : array of char to be send
// output : none
int udpserver :: send(char *message)
{
	string msg = message;
	int msg_length = msg.length();
	int slen = sizeof(si_other);

	int s = sendto(sockfd, message, msg_length, 0, (struct sockaddr*) &si_other, slen);

	return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// function that reads in the incoming data from client
// input : point of string
// output : integer variable 
int udpserver :: receive()
{
	unsigned int slen = sizeof(si_other);
	int r = recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
	
	//cout << "Client :" << buf << endl;
	return r;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//getting the buffer message
//input : null
//output : null
char* udpserver :: getBuf()
{
	return buf;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//clearing the buffer
//input : null
//output : null
void udpserver :: clearBuf()
{
	bzero(buf, sizeof(buf));
}
