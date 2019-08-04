#!/usr/bin/env python3

import socket
import threading
import time
import json
import requests
import time
import signal
import sys

def signal_handler(sig, frame):
    print('Fechando servidor!')
    for c in t:
        c.join()
    sys.exit(0)


class Cliente:
    def setId(self, id):
        self.id = id
    def setNsense(self,nsense):
        self.nsense = nsense

def sendFrq(conn,valor):
    conn.sendall(str("FRQ " + str(valor)).encode())

def sendOK(conn):
    conn.sendall("+OK".encode())

def sendLED(conn, led_estado):
    conn.sendall(("+LED "+str(led_estado)).encode())

def waitMessage(conn):
    return str(conn.recv(1024).decode("utf-8")).split()

def sendDEVLST(conn):
    if(len(conexoes)>0):
        resp = ""
        for id in conexoes:
            resp += "+ID " + str(id)
        conn.sendall(resp.encode())
    else:
        sendERROR(conn)

def sendMEAS(conn,id):
    if id in dados :
        d = dados[id][len(dados[id])-1]
        conn.sendall(("+DATA "+str(d)).encode())
    else:
        sendERROR(conn)

def sendERROR(conn):
    conn.sendall("+ERROR".encode())

def protocolo(cliente, conn, msg,dados):
    try:
        if(msg[0] == "IAM"):   
            cliente.setId(msg[1])
            sendOK(conn)
            conexoes[cliente.id] = conn
        elif(msg[0] == "SNS"):
            cliente.setNsense(msg[1])
            sendOK(conn)
        elif(msg[0]== "MEAS"):
            if int(msg[1]):  
                dados.setdefault(cliente.id,[]).append(int(msg[1]))
            try:
                    requests.post(WEB_SERVER+"/upload",json=json.dumps(dados))
            except:
                print("Erro de comunicação WEB")
        elif(msg[0] == "DEVLST"):
            sendDEVLST(conn)
        elif(msg[0] == "GETMEAS"):
            sendMEAS(conn,msg[1])
        elif(msg[0] == "TURN"):
            if msg[1] in conexoes:
                sendLED(conexoes[msg[1]],msg[2])
                sendOK(conn)
        else:
            sendERROR(conn)
    except:
        sendERROR(conn)


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

def servidor_tcp():
    HOST = ''  
    PORT = 65432
    
    # signal.signal(signal.SIGINT, signal_handler)
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        
        while True:
            conn, addr = s.accept()
            t.append(threading.Thread(target=cliente_connectado,args=(conn,addr)))
            t[-1].start()           

if __name__ == "__main__":
    WEB_SERVER = "http://192.168.0.153:8080"
    dados = {}
    conexoes = {}
    t = []
    web_conn = threading.Thread(target=verifica_estado)
    web_conn.start()
    servidor_tcp()