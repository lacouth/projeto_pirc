#include <iostream>
#include "mytcpserver.h"

#define SERVER_TCP_PORT 8000

using namespace std;

int main(){

    MyTcpServer connection(SERVER_TCP_PORT);

    connection.startListen(50);

    while(true){
        auto sock_id = connection.acceptConnection();
        string msg;
        do{
            msg = connection.receiveMessage();
            cout << msg <<endl;
        }while(msg.size()>0);
    }

    return 0;
}
