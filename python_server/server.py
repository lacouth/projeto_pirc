#!/usr/bin/env python3

import socket
import threading
import time
import json

from flask import Flask, render_template, redirect, request

app = Flask(__name__)

class Cliente:
    def setId(self, id):
        self.id = id
    def setNsense(self,nsense):
        self.nsense = nsense

def protocolo(cliente, conn, msg,dados):
    if(msg[0] == "IAM"):
        
        cliente.setId(msg[1])
        sendOK(conn)
    elif(msg[0] == "SNS"):
        cliente.setNsense(msg[1])
        sendOK(conn)
    elif(msg[0]== "MEAS"):
        
        dados.setdefault(cliente.id,[]).append(int(msg[1])) 



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

def sendOK(conn):
    conn.sendall("+OK".encode())

def waitMessage(conn):
    return str(conn.recv(1024).decode("utf-8")).split()


def cliente_connectado(conn,addr):
    with conn:
        cliente = Cliente()
        print('Connected by', addr) 
        while True:
            print(dados)
            data = waitMessage(conn)
            protocolo(cliente, conn, data,dados)
            
            

@app.route("/")
def rota_inicial():
    return render_template("index.html", dados = dados)

if __name__ == "__main__":
    dados = {}
    s = threading.Thread(target=servidor_tcp)
    s.start()
    app.run("0.0.0.0",port=8080) 
            