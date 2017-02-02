//  Write an application that has a menu and functionality control daemon, broadcasting and pipe operations. This will be your last assignment in this area, decide what functions you should include in the menu.
//
//  File : main.cpp
//
/*Program : Daytime Client Server application.
This programms perform following operations of client and server :

STEPS TO EXECUTE PROGRAM
-------------------------
1. Unzip the contents of client.zip
2. It contains make file. Run the make file to compile the program
3. Once done. A executable with name "c" will be generated
4. run the client with by type "./client 127.0.0.1 5000" on terminal
*/

//  Name : Priyanka Chordia.
//  Date : 11/28/14
//  Course : CSCI 511
//


//Header Files used for the program
#include "Client.h"
#include <iostream>
#include <stdlib.h>

// Standard namespace used so that we don't need to define a definition for every variable.
using namespace std;

/*Fn: main()

Description: Entry point of the program.

In: *time- pointer to convert into time.
server_address- contains the address of the server.
time- captures and stores the time

Out: N/A.

*/
int main(int argc, char **argv)
{
	if(argc == 3)
	{
		string server_address;
		int portno;
		char *time;

		server_address = argv[1];
		portno = atoi(argv[2]);

		client *cl;

		cl = new client(server_address, portno);
		
		if(cl->connect_to_server() == 0)
		{
			if(cl->receiveMessage() == 0)
			{
				time = cl->getServerReply();
				cout << time << endl;
			}
			cl->stop_client();
		}
	}
	else
	{
		cout << "Too few arguments. Pass parameters in the following format:" << endl;
		cout << "\tclient <server address> <portno>" << endl;
		return -1;
	}
	return 0;
}
