#include "protocol.h"

Protocol::Protocol(int sockfd) : socket(sockfd){}

Protocol::~Protocol()
{
}

void Protocol::handshake()
{
     char msg[MAX_MSG];
    try{
       
        recv(socket, msg, sizeof(msg), 0);
       
        if (stoi(msg) == TYPE::DEVICE)
        {
            type = TYPE::DEVICE;
        }
        else if (stoi(msg) == TYPE::USER)
        {
            type = TYPE::USER;
        }

        
    }catch(std::invalid_argument &e) {
        cout << msg << endl;
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

   // return "<h1>OI MUNDO</h1>";
}

 void Protocol::userCommunication(map<string,vector<int>> &dados){
    char recvMsg[MAX_MSG];
    char sndMsg[MAX_MSG];

    sprintf(sndMsg,"%d",MESSAGE::START);
    
    send(socket,sndMsg,strlen(sndMsg),0);

    try{
        recv(socket, recvMsg,sizeof(recvMsg),0);
        switch (stoi(recvMsg))
        {
        case MESSAGE::GETDEVICES:
            if(dados.size() > 0){
                string devices;
                for(auto e: dados){
                    devices+=e.first+",";
                }
                send(socket,devices.c_str(),devices.size()+1,0);
            }
            break;
        default:
            break;
        }
    }catch(char const* e){
        cout << e;
    }

    

 }
