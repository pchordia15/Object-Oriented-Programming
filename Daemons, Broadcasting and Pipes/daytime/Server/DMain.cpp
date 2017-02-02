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
#include "DaytimeServer.h"

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
    }

    return 0;
}

