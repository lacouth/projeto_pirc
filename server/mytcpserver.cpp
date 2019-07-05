#include "mytcpserver.h"

MyTcpServer::MyTcpServer(int porta)
{

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(porta);
    sockAcesso = socket(AF_INET, SOCK_STREAM, 0);

    try
    {
        if (bind(sockAcesso, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            throw "Erro no bind!";
    }
    catch (char const* erro)
    {
        cout << erro;
    }
}

MyTcpServer::~MyTcpServer()
{
    close(sockAcesso);
}

void MyTcpServer::startListen(int fila)
{
    try
    {
        if (listen(sockAcesso, fila) < 0)
            throw "Erro no listen!";
    }
    catch (char const* erro)
    {
        cout << erro;
    }
}

int MyTcpServer::acceptConnection()
{
    try
    {
        client_id = accept(sockAcesso, (struct sockaddr *)&client_addr, &tam_addr);
        if (client_id < 0)
            throw "Erro na conexão com o cliente\n";

        cout << "Conexão estabelecida" << endl;
        return client_id;
    }
    catch (char const* erro)
    {
        cout << erro;
        return -1;
    }
}

string MyTcpServer::receiveMessage()
{

    char msgServer[MAX_MSG] = {'\0'};
    try
    {
        if (recv(client_id, msgServer, sizeof(msgServer), 0) < 0)
            throw "Erro na recepção da mensagem!";
        return string(msgServer);
    }
    catch (char const* erro)
    {
        cout << erro;
        return 0;
    }
}

void MyTcpServer::threadClient(void *psockfd)
{
    char msgServer[MAX_MSG] = {'\0'};
    int sockfd = *(int *)psockfd;
    try
    {
        while (recv(sockfd, msgServer, sizeof(msgServer), 0) > 0)
        {   
            string key = "Cliente_" + to_string(sockfd);
            dados[key].push_back(stoi(msgServer));
            cout << key << " - " << msgServer << endl;
        }
        throw "Erro na recepção da mensagem!";
    }
    catch (char const* erro)
    {
        close(sockfd);
        cout << erro;
    }
}

void MyTcpServer::getData(){
    cout << dados.size();
    for(auto e : dados){
        cout << endl<<"Resumo: "<<e.first << " - " << e.second.size();
    }
}