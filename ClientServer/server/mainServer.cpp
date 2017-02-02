//  Write an application that has the following menu and functionality. Comments about the functionality of each menu option follow the ë//í
//
//  File : serverMain.cpp
//
/*Program : TCP Client Server application.
This programms perform following operations of client and server :
1) Get IP address and port of the client
// the server displays the address of all the clients it is aware of

2) Send IP address date and time of server to all clients
// the clients display the servers IP address, date and time

3) Kill a client
// The server sends a message to a given client and the client shuts down

4)  Get a directory listing of files from clients
// The server sends a request to get the directory listing of a given clients directory that the server specifies

5) Get clients system date and time.
// sends a request to clients to have them send their date and time. The server prints the date and time

STEPS TO EXECUTE PROGRAM
-------------------------
1. Unzip the contents of server.zip
2. It contains make file. Run the make file to compile the program
3. Once done. A executable with name "s" will be generated
4. run the server with by type "./s" on terminal
*/
//  Name : Priyanka Chordia.
//  Date : 11/14/14
//  Course : CSCI 511
//


#include "server.h"
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void pauseScreen();
void clearScreen();
void killClient(server *s);
void requestIP(server *s);
void requestPortNo(server *s);
void send_IP_Time(server *s);
void requestClientTime(server *s);
void requestDirectory(server *s);
void printDirectory(string content);
////////////////////////////////////////////////////////////////////////////////////////////////////	
int main()
{
	server s(5000);
	char msg[1024];
	int choice;
	string client_res;
	
	//starting server
	int rc = s.start();
	
	if (rc == 0)
	{
		while(1)
		{
			cout << "*************************************************" << endl;
			cout << "                  Server Menu" << endl;
			cout << "*************************************************" << endl;
			cout << "1. Get IP address and port no of client" << endl;
			cout << "2. Send to IP address and time to all clients" << endl;
			cout << "3. Kill client" << endl;
			cout << "4. Get directory listing of files from clients." << endl;
			cout << "5. Get clients system date and time." << endl;
			cout << "6. Exit" << endl;
			cout << "*************************************************" << endl;
			cout << "Enter Your choice: ";
			cin >> choice;
			
			switch(choice)
			{
				case 1:
					clearScreen();
					requestIP(&s);
					cout << "Client :" << endl;
					cout << "\tIP Address:";
					s.readData(&client_res);
					cout << client_res << endl;
					requestPortNo(&s);
					cout << "\tPort No:";
					s.readData(&client_res);
					cout << client_res << endl;
					pauseScreen();
					break;
				case 2:
					clearScreen();
					cout << "Server time sent to client." << endl;
					send_IP_Time(&s);
					pauseScreen();
					break;
				case 3:
					clearScreen();
					cout << "Sending kill signal sent to client." << endl;
					killClient(&s);
					pauseScreen();
					break;
				case 4:
					clearScreen();
					cout << "Request sent to client for directory content." << endl;
					requestDirectory(&s);
					s.readData(&client_res);
					printDirectory(client_res);
					pauseScreen();
					break;
				case 5:
					clearScreen();
					cout <<	"Request sent to client for date and time." << endl;
					cout << "Client: ";
					requestClientTime(&s);
					s.readData(&client_res);
					cout << client_res << endl;
					pauseScreen();
					break;
				case 6:
					cout << "Sending kill signal to all clients." << endl;
					killClient(&s);
					cout << "Closing server socket." << endl;
					s.stop();
					cout << "Terminating program." << endl;
					return 0;
				default:
					cout << "Invalid option!!" << endl;
			}
			
			//s.readData();
		}	
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//function to pausescreen
//input : none
//output: none
void pauseScreen()
{
	cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
	cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
	cin.clear();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//function to clear screen
// input : none
// output : none
void clearScreen()
{
	cout << "\033[H\033[J";
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// a function to send kill signal to client
// input : pointer to server instance
// output : none
void killClient(server *s)
{
	char q[] = "quit;";
	s->sendData(q);
	int cli = s->stopClient();
	cout << "Killed client: " << cli << endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// function to request IP address to client
// input : a instance of server
// output : none
void requestIP(server *s)
{
		char ip[] = "ipaddr;";
		s->sendData(ip);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// function to request to port no of client
// input : a instance of server
// output : none
void requestPortNo(server *s)
{
	char port[] = "portno;";
	s->sendData(port);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// a function to send IP address and time of server to client
// input : a instance of server
// output : none
void send_IP_Time(server *s)
{
	char *ip = s->getIPAddress();
	string time = s->getCurrentTime();
	string iptime = "iptime;";
	iptime.append(ip);
	iptime.append(";");
	iptime.append(time);
	strcpy(ip, iptime.c_str());
	s->sendData(ip);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//A function to request client to send it's time
// input : pointer of server instance
// output : none
void requestClientTime(server *s)
{
	char client_time[] = "ctime;";
	s->sendData(client_time);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//a function to send a request to client for content directory
// input : pointer to server instance
// output : none
void requestDirectory(server *s)
{
	char directory[] = "directory_content;";
	s->sendData(directory);
}
////////////////////////////////////////////////////////////////////////////////////////////////////	
//function to print the directory contents on screen
//input: string 
//outout: none
void printDirectory(string files)
{
	vector<string> object;
	stringstream s_str(files);
	string file;
	while(getline(s_str, file, ';'))
	{
		object.push_back(file);
	}
	vector<string> :: iterator itr;
	unsigned long max_filename_length = 0;
	string filename;
	int column_counter = 0, COLUMN = 3;
	
	for(itr = object.begin(); itr != object.end(); itr++)
	{
		filename = *itr;
		unsigned long filename_length = filename.length();
		
		if( max_filename_length < filename_length)
		{
			max_filename_length = filename_length;
		}
	}
	if(max_filename_length > 35)
	{
		COLUMN = 2;
	}
	for(int i = 0; i < 120; i++)
	{
		cout << "-";
	}
	cout << endl;
	cout << "Client Folder Contents " << endl;
	for(int i = 0; i < 120; i++)
	{
		cout << "-";
	}
	cout << endl;
	for(itr = object.begin(); itr != object.end(); itr++)
	{
		filename = *itr;
		unsigned long filename_length = filename.length();
		unsigned long length_diff = max_filename_length - filename_length;
		
		cout << filename;
		column_counter++;
		
		for(unsigned long i = 0;i <= length_diff; i++)
		{
			cout << " ";
		}
		
		if(column_counter == COLUMN)
		{
			column_counter = 0;
			cout << endl;
		}
		
	}
	cout << endl;
	
	for(int i = 0; i < 120; i++)
	{
		cout << "-";
	}
	cout << endl;
}