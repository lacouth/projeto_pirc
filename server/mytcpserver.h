#ifndef MyTcpServer_H
#define MyTcpServer_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <map>
#include <vector>

#include "protocol.h"

using namespace std;

static map<string,vector<int>> dados;

class MyTcpServer
{
private:
    int sockAcesso;
    struct sockaddr_in serv_addr;
    struct sockaddr_storage client_addr;
    socklen_t tam_addr = sizeof(serv_addr);
    int client_id;
    

public:
    MyTcpServer(int porta);
    ~MyTcpServer();
    void startListen(int fila);
    int acceptConnection();
    string receiveMessage();
    static void getData();
    static void threadClient(void *psockfd);
};

#endif // !MyTcpServer_H
