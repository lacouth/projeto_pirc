#include <iostream>
#include <thread>
#include <csignal>
#include <cerrno>
#include "mytcpserver.h"

#define SERVER_TCP_PORT 8000

using namespace std;

void terminateServer(int signum){};


int main(){

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
	sa.sa_handler = terminateServer;
	sigaction(SIGINT, &sa, NULL);


    MyTcpServer server(SERVER_TCP_PORT);
    vector<thread> th;
    vector<int> clients;

    server.startListen(50);

    while(true){
        auto sock_id = server.acceptConnection();
        if(sock_id < 0){
            if (errno == EINTR) break;
        }else{
            th.push_back(thread(MyTcpServer::threadClient,&sock_id));
            clients.push_back(sock_id);
        }
    }

    cout << "Finalizando o servidor\n";
    for(int i=0; i<th.size();++i){
        close(clients[i]);
        if(th[i].joinable())
            th[i].join();
    }

    server.getData();

    
    return 0;
}
