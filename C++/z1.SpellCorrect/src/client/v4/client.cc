#include "SocketIO.h"
#include "TcpConnection.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include<netinet/in.h>
#include <arpa/inet.h>
using namespace std;
int main()
{
    int socket_fd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sockaddr_in_0;
    bzero(&sockaddr_in_0,sizeof(sockaddr_in_0));
    sockaddr_in_0.sin_port = htons( (short) 1234 );
    sockaddr_in_0.sin_family = AF_INET;
    sockaddr_in_0.sin_addr.s_addr = inet_addr("172.19.210.35");
    connect(socket_fd,(struct sockaddr *) &sockaddr_in_0,sizeof(sockaddr_in_0));
    string sendWord,recvWord;
    //wd::SocketIO s0(socket_fd);
    wd::TcpConnection t0(socket_fd,nullptr); 
    while(cin >> sendWord)
    {
        sendWord += "\n";
        t0.send(sendWord);
        recvWord = t0.receive();
        //s0.writen(word.c_str(),word.size());
        //send(socket_fd,word.c_str(),word.size(),0);
        //memset(out,0,sizeof(1024 * sizeof(char)));
        //s0.readn(out,1024);
        //recv(socket_fd,out,1024,0);
    }
    return 0;
}

