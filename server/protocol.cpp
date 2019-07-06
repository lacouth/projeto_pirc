#include "protocol.h"

Protocol::Protocol(int sockfd) : socket(sockfd) {}

Protocol::~Protocol()
{
}

void Protocol::handshake()
{
    char msg[MAX_MSG];
    recv(socket, msg, sizeof(msg), 0);
    if (stoi(msg) == DEVICE)
    {
        type == DEVICE;
    }
    else if (stoi(msg) == USER)
    {
        type == USER;
    }
}

TYPE Protocol::getType()
{
    return type;
}

void Protocol::deviceCommunication(map<string, vector<int>> &dados)
{
    char msg[MAX_MSG];
    char sndMsg[MAX_MSG];


    recv(socket, msg, sizeof(msg), 0);
    device_id = string(msg);
    memset(msg, 0, MAX_MSG);

    sprintf(sndMsg,"%d",START);

    if (send(socket, sndMsg, strlen(sndMsg)+1, 0) > 0){
        while (recv(socket, msg, sizeof(msg), 0) > 0)
        {
            dados[device_id].push_back(stoi(msg));
            cout << device_id << " - " << msg << endl;
            memset(msg, 0, MAX_MSG);
        }
    }
}
