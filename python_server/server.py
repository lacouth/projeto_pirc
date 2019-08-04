#!/usr/bin/env python3

import socket
import threading
import time
import json
import requests
import time

class Cliente:
    def setId(self, id):
        self.id = id
    def setNsense(self,nsense):
        self.nsense = nsense

def protocolo(cliente, conn, msg,dados):
    if(msg[0] == "IAM"):   
        cliente.setId(msg[1])
        sendOK(conn)
        conexoes[cliente.id] = conn
    elif(msg[0] == "SNS"):
        cliente.setNsense(msg[1])
        sendOK(conn)
    elif(msg[0]== "MEAS"):
        try:
            if int(msg[1]):  
                dados.setdefault(cliente.id,[]).append(int(msg[1]))
                requests.post(WEB_SERVER+"/upload",json=json.dumps(dados))
        except:
            print("Erro de comunicação")

def servidor_tcp():
    HOST = ''  
    PORT = 8000
    t = []
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        
        while True:
            conn, addr = s.accept()
            t.append(threading.Thread(target=cliente_connectado,args=(conn,addr)))
            t[-1].start()

def sendFrq(conn,valor):
    conn.sendall(str("FRQ " + str(valor)).encode())

def sendOK(conn):
    conn.sendall("+OK".encode())

def sendLED(conn, led_estado):
    conn.sendall(("+LED "+str(led_estado)).encode())

def waitMessage(conn):
    return str(conn.recv(1024).decode("utf-8")).split()

def cliente_connectado(conn,addr):
    with conn:
        cliente = Cliente()
        print('Conexão com ', addr) 
        while True:
            data = waitMessage(conn)
            protocolo(cliente, conn, data,dados)

def verifica_estado():
    while(True):
        r = requests.get(WEB_SERVER+"/get_estado")
        estado = r.json()
        for id in estado:
            if id in conexoes:
                sendLED(conexoes[id],estado[id])
        
        # time.sleep(2)

            

if __name__ == "__main__":
    WEB_SERVER = "http://192.168.0.153:8080"
    dados = {}
    conexoes = {}
    s = threading.Thread(target=verifica_estado)
    s.start()
    servidor_tcp()