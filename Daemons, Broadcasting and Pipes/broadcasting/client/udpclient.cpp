// DESCRIPTION
// This file contains the client class and it will be used during the execution in main.cpp.
// Besides constructors, the member functions of client class are: connect_to_server, receive, 
//send, getBuff and clearBuff
//
#include "udpclient.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

udpclient :: udpclient()
{

}

udpclient :: ~udpclient()
{

}
void udpclient :: error(char *message)
{
	perror(message);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fn: connect_to_server
//
// Description: Creates the socket, define the socket parameters and makes an attempt of connection with the client to the server.
//
// Inputs: n/a
//
// Output: int 0/-1 (the value means if was successfull or occurred an error)
//
int udpclient :: connect_to_server()
{
	cout << "Connecting to Server..." << endl;
	cout << "\tOpening socket..." ;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if(sockfd == -1)
	{
		error((char*)"Socket");
		return -1;
	}
	cout << "[succeess]" << endl;
	
	bzero(&si_other, sizeof(si_other));

	si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

	int broadcastOn = 1;
	int checkCall = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastOn, 4);

	if (inet_aton(SERVER , &si_other.sin_addr) == 0)
    {
        error((char*)"inet aton");
        return -1;
    }
	cout << "connected" << endl;
	return 0;
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fn: send
//
// Description: Send a message to the server
//
// Inputs: char msg[]
//
// Output: int rc = 0/-1 (the value means if was successfull or occurred an error)
//
int udpclient :: send(char *message)
{
	string msg = message;
	int msg_length = msg.length();
	int slen = sizeof(si_other);

	int s = sendto(sockfd, message, msg_length , 0 , (struct sockaddr *) &si_other, slen);
	
	return s;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fn: receive
//
// Description: Receive a message from the server
//
// Inputs: n/a
//
// Output: int rc = 0/-1 (the value means if was successfull or occurred an error)
//
int udpclient :: receive()
{
	unsigned int slen = sizeof(si_other);
	int r = recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
	
	return r;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fn: getBuff
//
// Description: obtain buffer
//
// Inputs: n/a
//
// Output: n/a
//
char* udpclient :: getBuf()
{
	return buf;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fn: clearBuff
//
// Description: clear buffer
//
// Inputs: n/a
//
// Output: n/a
//
void udpclient :: clearBuf()
{
	bzero(buf, sizeof(buf));
}
