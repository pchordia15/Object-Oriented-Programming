// DESCRIPTION
// This file contains the client class and it will be used during the execution in main.cpp.
// Besides constructors, the member functions of client class are: connect_to_server, receiveMessage, 
//sendMessage, stop_client and getServerReply
//
#include "Client.h"
#include <iostream>
#include <string>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

client :: client()
{

}

client :: client(string hostname, int pno)
{
	this->host = hostname;
	this->portno = pno;
}

client :: ~client()
{

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
int client :: connect_to_server()
{
	cout << "Trying to connect to with server..." << endl;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	cout << "\tCreating socket..." ;
	if(sock == -1)
	{
		cout << "[Failed]" << endl;
		cout << "\t\tERROR : Unable to create socket!!" << endl;
		return -1;
	}
	
	cout << "[Success]" << endl;
	
	server.sin_addr.s_addr = inet_addr(host.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(portno);
    
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        cout << "ERROR: Unable to connect with server!!" << endl;
        return -1;
    }

    cout << "Connected to server." << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fn: receiveMessage
//
// Description: Receive a message from the server
//
// Inputs: n/a
//
// Output: int rc = 0/-1 (the value means if was successfull or occurred an error)
//
int client :: receiveMessage()
{
	int rc = 0;
	
	bzero(server_reply, 1024);
	if( recv(sock, server_reply, 1024, 0) < 0)
	{
		cout << "ERROR : Unable to receive message from server." << endl;
		return -1;
	}
	//cout << "Server: " << server_reply << endl;
	return rc;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fn: sendMessage
//
// Description: Send a message to the server
//
// Inputs: char msg[]
//
// Output: int rc = 0/-1 (the value means if was successfull or occurred an error)
//
int client :: sendMessage(char msg[])
{
	int rc = 0;
	
	if( send(sock , msg , strlen(msg) , 0) < 0)
    {
        cout << "ERROR: Unable to send message to server." << endl;
        return -1;
    }
    return rc;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fn: stop_client
//
// Description: Stops/kills the client
//
// Inputs: n/a
//
// Output: n/a
//
void client :: stop_client()
{
	close(sock);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fn: getServerReply
//
// Description: Returns the value of private member server_reply
//
// Inputs: n/a
//
// Output: server_reply
//
char* client :: getServerReply()
{
	return server_reply;
}
