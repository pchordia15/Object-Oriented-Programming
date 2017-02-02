//  File : ClientServerPipes.cpp
// This uses concept of pipes for interprocess communication.
// Thereare two processes one is Parent(client) and other is child(server).
// Client sends message to server and server prints it.
// User acts as client.User gives message from standard input.
//
//
//  Name : Priyanka Chordia.
//  Date : 11/28/14
//  Course : CSCI 511
//


#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <wait.h>
#include <iostream>
#include <cstring>
#include    <syslog.h>
#include <sys/signal.h>
#include <fcntl.h>

using namespace std;

#define buffersize 256
///////////////////////////////////////////////////////////////////////////////
/*
client():
    This method is called by parent process.
    It takes input from user and sends it to server process throught pipe.
IN: readfd: This is discriptor of pipe2 which is used for reading message send by server process.
    writefd: This is discriptor of pipe1 which is used for writting message to server process.
OUT:NA
*/
void client (int readfd, int writefd)
{
    char rbuffer[buffersize], wbuffer[buffersize];
    string writemsg;
    cout<<"Enetr String for client....(END to end the communication)"<<endl;

    while(1)
    {
        cout<<"Client:";
        getline(cin,writemsg);
        bzero(rbuffer,buffersize);
        write(writefd,writemsg.c_str(),buffersize);
        read(readfd,rbuffer,buffersize);
        if(writemsg=="END")
            break;
    }

}
///////////////////////////////////////////////////////////////////////////////
/*
server():
    This method is called by child process.
    It reads message send by client process and prints it on standard output as echo.
IN: readfd: This is descriptor of pipe1 which is used for reading message send by client process.
    writefd: This is descriptor of pipe2 which is used for writting message to client process.
OUT:NA
*/
void server (int readfd, int writefd)
{
    char rbuffer[buffersize], wbuffer[buffersize];
    string writemsg;
    while(1)
    {
        bzero(rbuffer,buffersize);
        read(readfd,rbuffer,buffersize);
        if(strcmp(rbuffer,"END")==0)
            break;
        cout<<"Server: echo>"<<rbuffer<<endl;
        writemsg="echo>";
        writemsg.append(rbuffer);
        write(writefd,writemsg.c_str(),buffersize);
        writemsg.clear();
    }

}
///////////////////////////////////////////////////////////////////////////////
/*
main():
    This is entry point of program.
    It creates two pipes, and then a child process.
IN:NA
OUT:NA
*/
int main()
{
    int pipe1 [2] , pipe2 [2];
    pid_t childpid;
    /* create two pipes */
    pipe(pipe1);
    pipe(pipe2);
    if ( (childpid = fork () ) == 0)  /* child */
    {
        close (pipe1 [1] ) ;
        close (pipe2 [0] ) ;
        server (pipe1 [0] , pipe2 [1] ) ;
        exit( 0) ;
    }
    /* parent */
    close (pipe1 [0] ) ;
    close (pipe2 [1] ) ;
    client( pipe2 [0] , pipe1 [1] ) ;
    waitpid(childpid, NULL, 0); /* wait for child to terminate */
    return 0;
}
