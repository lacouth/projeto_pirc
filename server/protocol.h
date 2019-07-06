#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <map>
#include <vector>

#include "../common/enums.h"

using namespace std;

class Protocol
{
private:
    int socket;
    TYPE type;
    string device_id;
public:
    Protocol(int sockfd);
    ~Protocol();

    void handshake();
    TYPE getType();

    void deviceCommunication(map<string,vector<int>> &dados);


};

#endif // !PROTOCOL_H



