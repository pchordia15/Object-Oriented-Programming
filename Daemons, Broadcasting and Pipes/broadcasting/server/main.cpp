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
4. run the client with by type "./c" on terminal
*/

//  Name : Priyanka Chordia.
//  Date : 11/28/14
//  Course : CSCI 511
//


//Header Files used for the program
#include "udpserver.h"
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

void error(char* message);

/*Fn: main()

Description: Entry point of the program.

In: recv,snd- to receive and send the message.

Out: N/A.

*/
int main()
{
	udpserver *us = new udpserver();
	int recv, snd;
	char *response;

	int start = us->start();
	
	if(start == 0)
	{
		while(1)
		{
			us->clearBuf();
			recv = us->receive();
			if(recv == -1)
			{
				//error((char *)"Receive");
			}
			response = us->getBuf();
			snd = us->send(response);
			if(snd == -1)
			{
				//error((char *)"Send");
			}
		}
	}
}

void error(char* message)
{
	perror(message);
}
	
