//  Write an application that has a menu and functionality control daemon, broadcasting and pipe operations. This will be your last assignment in this area, decide what functions you should include in the menu.
//
//  File : main.cpp
//
/*Program : Broadcasting client server application.
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
#include "udpclient.h"
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

void error(char *message);

/*Fn: main()

Description: Entry point of the program.

In: *message- pointer to store the message.
    *echo- pointer to echo the message.

Out: N/A.

*/
int main()
{
	int cn, sn, rc;
	char *message;
	string m;
	char *echo;

	udpclient *uc = new udpclient();

	cn = uc->connect_to_server();
	
	if(cn == 0)
	{
		while(1)
		{
			uc->clearBuf();
			cout << "Enter your message: ";
			cin >> m;
			message = (char *)m.c_str();
			sn = uc->send(message);
			if(sn == -1)
			{
				error((char*)"Send");
			}

			rc = uc->receive();
			if(rc == -1)
			{
				error((char*)"Receive");
			}
			else
			{
				echo = uc->getBuf();
				cout << "Echo: " << echo << endl;
			}
		}
	}
	return 0;
}

/*Fn: errorn()

Description: to display error message.

In: message: to display the error message.

Out: N/A.

*/
void error(char *message)
{
	error(message);
}
