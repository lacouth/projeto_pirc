#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SERVER_TCP_PORT 8000

#define MAX_MSG 1024

using namespace std;

int main(){
    
    struct sockaddr_in serv_addr;
    struct sockaddr_storage client_addr;
    socklen_t tam_addr = sizeof(serv_addr);

    serv_addr.sin_family = AF_INET;                 /* Endereco da familia IP */
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  /* de qualquer endereco   */
	serv_addr.sin_port = htons(SERVER_TCP_PORT);

    auto sockAcesso = socket(AF_INET, SOCK_STREAM, 0);
    
    
    if(bind(sockAcesso, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        cout<<"Erro no bind\n";
        return 1;
    }
    
    if(listen(sockAcesso,50) < 0 ){
        cout << "Erro no listen";
        return 1;
    }   

    while(true){
        cout << "Processo" << getpid() << "Aguardando cliente"<<endl;
        auto serv_addr = accept(sockAcesso,(struct sockaddr *) &client_addr, &tam_addr);
        if(serv_addr < 0){
            return 1;
        }
        cout << "Conexão estabelecida"<<endl;
        char msgServer[MAX_MSG] = {'\0'};
        int n_bytes;

        while((n_bytes = recv(serv_addr,msgServer,sizeof(msgServer),0)) != 0){
            if(n_bytes < 0){
                cout << "Erro na recepção\n";
                break;
            }
            cout << "[Processo:  " << getpid() << " Mensagem: " << msgServer << endl;
            if(send(serv_addr,msgServer,strlen(msgServer)+1,0)<0){
                cout << "Erro no envio\n";
                return 1;
            }
            memset(msgServer,0,MAX_MSG);
        }
        cout << "[Processo %d] Tarefas Concluidas...\n" <<getpid() <<endl;
        close(sockAcesso);    
    }

    return 0;
}