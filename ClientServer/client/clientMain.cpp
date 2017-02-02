//  Write an application that has the following menu and functionality. Comments about the functionality of each menu option follow the ë//í
//
//  File : clientMain.cpp
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
1. Unzip the contents of client.zip
2. It contains make file. Run the make file to compile the program
3. Once done. A executable with name "c" will be generated
4. run the client with by type "./c" on terminal
*/
//  Name : Priyanka Chordia.
//  Date : 11/14/14
//  Course : CSCI 511
//


//Header Files used for the program
#include "client.h"
#include <string>
#include <sstream>
#include <iostream>

// Standard namespace used so that we don't need to define a definition for every variable.

using namespace std;

void toUpper(string &str);
///////////////////////////////////////////////////////////////////////////////////////////////

/*Fn: main()

Description: Entry point of the program.

In: *m- pointer to convert into string.
    server_res- contains the string command to be passed.
    pos- points to the position.

Out: N/A.

*/

int main()
{
	//char msg[1024];
	char *m;
	string server_res;
	int pos;
	client c("127.0.0.1", 5000);
	
	if(c.connect_to_server() == 0)
	{
		while(1)
		{
			if(c.receiveMessage() == 0)
			{
				m = c.getServerReply();
				server_res = m;
				string command = server_res;
				stringstream str_stream(command);
				getline(str_stream, command, ';');
				toUpper(command);
				if( command.compare("QUIT") == 0)
				{
					string data;
					str_stream.str(server_res);
					getline(str_stream, data, ';');
					cout << "Server: " << data << endl;
					cout << "Terminating client on server request." << endl;
					c.stop_client();
					break;
				}
				if( command.compare("IPADDR") == 0)
				{
					string data;
					str_stream.str(server_res);
					getline(str_stream, data, ';');;
					cout << "Server: " << data << endl;
					c.sendMessage(c.getIPAddress());
				}
				if ( command.compare("PORTNO") == 0)
				{
					string data;
					str_stream.str(server_res);
					getline(str_stream, data, ';');
					cout << "Server: " << data << endl;
					string pno_str = to_string(c.getPortNo());
					char *pno = (char *)pno_str.c_str();
					c.sendMessage(pno);
				}
				if ( command.compare("IPTIME") == 0)
				{
					string data;
					while(getline(str_stream, data, ';'))
					{
						cout << "Server: " << data << endl;
					}
				}
				if ( command.compare("CTIME") == 0 )
				{
					string data;
					str_stream.str(server_res);
					getline(str_stream, data, ';');
					cout << "Server: " << data << endl;
					string ctime = c.getCurrentTime();
					char *time = (char *)ctime.c_str();
					c.sendMessage(time);
				}
				if ( command.compare("DIRECTORY_CONTENT") == 0)
				{
					string data;
					str_stream.str(server_res);
					getline(str_stream, data, ';');
					cout << "Server: " << data << endl;
					string dc = c.readDirectory(".");
					char *dir = (char *)dc.c_str();
					c.sendMessage(dir);
				}
			}
		}
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////
/*Fn: toUpper()

Description: This function converts the string in upper case.

In: str- contains the string to be converted into upper case.

Out: The string is converted into upper case.

*/
void toUpper(string &str)
{
	for(unsigned int i = 0; i < str.length(); i++)
	{
		str[i] = toupper(str[i]);
	}
}