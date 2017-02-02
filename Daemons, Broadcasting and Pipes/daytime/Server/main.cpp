//  Write an application that has a menu and functionality control daemon, broadcasting and pipe operations. This will be your last assignment in this area, decide what functions you should include in the menu.
//
//  File : main.cpp
//
/*Program : Daytime Client Server application.
This programms perform following operations of client and server :


*/

//  Name : Priyanka Chordia.
//  Date : 11/28/14
//  Course : CSCI 511
//


//Header Files used for the program
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "DaytimeServer.h"

using namespace std;

/*Fn: main()

Description: Entry point of the program.

In: N/A.

Out: N/A.

*/
int main()
{
	DaytimeServer *ds = new DaytimeServer(5000);
	char msg[1024];

	int rc = ds->start();

	if(rc == 0)
	{
		while(1)
		{
			int accept_rc = ds->acceptConnection();
			if(accept_rc < 0)
			{
				return -1;
			}
			string time = ds->getCurrentTime();
			time.copy(msg, time.length(), 0);
			ds->sendData(msg);
			ds->closeClientSocket();
		}
	}
	
	return 0;
}
