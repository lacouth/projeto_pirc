#!/usr/bin/env python3

''' Biblioteca com as funções auxiliares ao servidor TCP-IoT '''
import socket
import threading
import requests
from cliente import Cliente
from protocolo import protocolo,waitMessage,sendLED

def cliente_connectado(conn,addr,dados,conexoes,WEB_SERVER):
    with conn:
        cliente = Cliente()
        print('Conexão com ', addr) 
        while True:
            data = waitMessage(conn)
            protocolo(cliente, conn, data,dados,conexoes,WEB_SERVER)

def verifica_estado(WEB_SERVER,conexoes):
    while(True):
        r = requests.get(WEB_SERVER+"/get_estado")
        estado = r.json()
        for id in estado:
            if id in conexoes:
                sendLED(conexoes[id],estado[id])

def servidor_tcp(t, dados, conexoes,HOST='', PORT=65432,WEB_SERVER=''):
        
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        
        while True:
            conn, addr = s.accept()
            t.append(threading.Thread(target=cliente_connectado,args=(conn,addr,dados,conexoes,WEB_SERVER)))
            t[-1].start()