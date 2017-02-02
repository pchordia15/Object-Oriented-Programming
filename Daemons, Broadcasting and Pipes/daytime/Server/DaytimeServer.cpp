/*
DaytimeServer.cpp files contains all the definition for server class.
DaytimeServer class is the class that provide the services for server to run.
*/
#include "DaytimeServer.h"
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
//Default constructor
DaytimeServer :: DaytimeServer()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Parameterized constructor
// input : port no
DaytimeServer :: DaytimeServer(int portno)
{
	this->portno = portno;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Default destructor
DaytimeServer :: ~DaytimeServer()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Function that starts the server
// input : none
// output : integer value that shows the status of with which server exited.
int DaytimeServer :: start()
{
	sockfd = socket(AF_INET , SOCK_STREAM , 0);
	
	if(sockfd == -1)
	{
				error("Unable to create Socket!!");
		return -1;
	}
	
	serv_add.sin_family = AF_INET;
	serv_add.sin_addr.s_addr = INADDR_ANY;
	serv_add.sin_port = htons(portno);
	
	if(bind(sockfd, (struct sockaddr *)&serv_add, sizeof(serv_add)) < 0 )
	{
				return -1;
	}
		
	listen(sockfd, 5);
	
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// function that reads in the incoming data from client
// input : point of string
// output : integer variable 
int DaytimeServer :: acceptConnection()
{
	//accept connection form incoming client
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &n);
	
	if( newsockfd < 0)
	{
			return -1;
	}
	return newsockfd;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// function that reads in the incoming data from client
// input : point of string
// output : integer variable 
int DaytimeServer :: readData(string *client_response)
{
	int read_size = recv( newsockfd, client_msg, 1024, 0);
	*client_response = client_msg;
	bzero(client_msg, 1024);
	
	return read_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// function to send data to client
// input : array of char to be send
// output : none
void DaytimeServer :: sendData(char msg[])
{
	write(newsockfd, msg, strlen(msg));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// function to display error message
// input : pointer of char containing message
// output : none
void DaytimeServer :: error(string message)
{
	const char *msg = message.c_str();
	perror(msg);
	exit(1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//function to get system date and time
//input : null
//output : string form time
string DaytimeServer :: getCurrentTime()
{
    time_t ticks;

	ticks = time(NULL);

	char buff[1024];

	snprintf(buff,sizeof(buff), "%.24s ", ctime(&ticks));

	string current_time = buff;
    
    return current_time;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//closing client socket
//input : null
//output : null
void DaytimeServer :: closeClientSocket()
{
	close(newsockfd);
}
