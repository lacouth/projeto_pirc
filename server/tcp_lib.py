#!/usr/bin/env python3

''' Biblioteca com as funções auxiliares ao servidor TCP-IoT '''
import socket
import threading
import requests
from cliente import Cliente
from protocolo import protocolo,waitMessage,sendLED

class TCP_SERVER:
    def __init__(self,WEB_SERVER,HOST='',PORT=65432):
        self.WEB_SERVER = WEB_SERVER
        self.HOST = HOST
        self.PORT = PORT
        self.dados = {}
        self.conexoes = {}
        self.threads = []

    def cliente_connectado(self,conn,addr):
        with conn:
            cliente = Cliente()
            print('Conexão com ', addr) 
            while True:
                data = waitMessage(conn)
                protocolo(cliente, conn, data,self.dados,self.conexoes,self.WEB_SERVER)

    def verifica_estado(self):
        while(True):
            r = requests.get(self.WEB_SERVER+"/get_estado")
            estado = r.json()
            for id in estado:
                if id in self.conexoes:
                    sendLED(self.conexoes[id],estado[id])

    def start(self):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.bind((self.HOST, self.PORT))
            s.listen()
            while True:
                conn, addr = s.accept()
                self.threads.append(threading.Thread(target=self.cliente_connectado,args=(conn,addr)))
                self.threads[-1].start()