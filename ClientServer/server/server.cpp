/*
	Server.cpp files contains all the definition for server class.
	Server class is the class that provide the services for server to run.
*/
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <time.h>
#include <ctime>

using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////
//Default constructor
server :: server()
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Parameterized constructor
// input : port no
server :: server(int pno)
{
	this->portno = pno;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Default destructor
server :: ~server()
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Function that starts the server
// input : none
// output : integer value that shows the status of with which server exited.
int server :: start()
{
	cout << "Starting server..." << endl;
	
	cout << "\tcreating socket...";
	sockfd = socket(AF_INET , SOCK_STREAM , 0);
	
	if(sockfd == -1)
	{
		cout << "[failed]" << endl;
		cout << "ERROR : Unable to create Socket!!" << endl;
		return -1;
	}
	cout << "[success]" << endl;
	
	serv_add.sin_family = AF_INET;
	serv_add.sin_addr.s_addr = INADDR_ANY;
	serv_add.sin_port = htons(portno);
	
	cout << "\tBinding server to address...";
	if(bind(sockfd, (struct sockaddr *)&serv_add, sizeof(serv_add)) < 0 )
	{
		cout << "[failed]" << endl;
		cout << "ERROR : Binding failed!!!" << endl;
		return -1;
	}
	cout << "[success]" << endl;
	
	//cout << "Waiting";
	cout << "Server started." << endl; 
	cout << "Waiting for connection..." << endl;
	
	//waiting for connection
	
	listen(sockfd, 5);
	
	//accept connection form incoming client
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &n);
	
	if( newsockfd < 0)
	{
		cout << "[failed]" << endl;
		cout << "ERROR: Unable to accept connection from client." << endl;
		return -1;
	}
	cout << "[connected]" << endl;	
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// function that reads in the incoming data from client
// input : point of string
// output : integer variable 
int server :: readData(string *client_response)
{
	int read_size = recv( newsockfd, client_msg, 1024, 0);
	//cout << client_msg << endl;
	*client_response = client_msg;
	bzero(client_msg, 1024);
	
	return read_size;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// function to send data to client
// input : array of char to be send
// output : none
void server :: sendData(char msg[])
{
	//write(newsockfd, client_msg, strlen(client_msg));
	write(newsockfd, msg, strlen(msg));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// function to display error message
// input : pointer of char containing message
// output : none
void server :: error(char *message)
{
	perror(message);
	exit(1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//function to stop server
//input : none
//output : none
void server :: stop()
{
	close(sockfd);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//function to stop client
// input none
// output : int file descriptor of client closed
int server :: stopClient()
{
	close(newsockfd);
	return newsockfd;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//Function to get IP address of client
//input : none
//output : pointer of char containing ip address of server
char* server :: getIPAddress()
{
	return inet_ntoa(serv_add.sin_addr);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//function to get system date and time
//input : null
//output : string form time
string server :: getCurrentTime()
{
    time_t t = time(0);
    
    struct tm *now = localtime(&t);
    
    string currentTime = to_string(now->tm_year + 1900) + "/" + to_string(now->tm_mon + 1) + "/" + to_string(now->tm_mday) + to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);
    
    return currentTime;
}