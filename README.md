<div style="text-align: justify"

# Projeto de Protocolos de Interconexão de Redes de Computadores - 2019.1

### Grupo

- Gabriel Borsero Estrela Bernardo - 20181370004
- Patric Lacouth da Silva - 20191370047



### Descrição do Projeto

<div style="text-align: justify">

​	Trata-se de um projeto que busca integrar dispositivos IoT com clientes através de um servidor.

​	A arquitetura utilizará o protocolo de transporte TCP para viabilizar a comunicação entre sensores e um servidor, e desse servidor com clientes locais. O sensores emitirão informações sobre luminosidade e temperatura que serão repassados dinamicamentes aos clientes que terão acesso a esses dados através de uma página web.

​	O módulo dos sensores será escrito em C++ enquanto que o módulo do servidor e do cliente será escrito em Python. Servidor e cliente se comunicarão através da aplicação web *Flask* que utiliza o protocolo de aplicação HTTP.	

​	Segue abaixo uma esquematização do projeto proposto: </div>

![undefined (1)](/home/borserog/Downloads/undefined (1).png)

