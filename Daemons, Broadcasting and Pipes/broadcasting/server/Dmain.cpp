/*
    Program to demostrate how to implement daemons.

*/
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include "udpserver.h"

using namespace std;

int main()
{
    pid_t pid, sid;

    pid = fork();
    if(pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if(pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if(sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if(chdir("/") < 0)
    {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while(1)
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

    return 0;
}
