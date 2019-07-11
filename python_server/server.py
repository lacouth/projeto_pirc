#!/usr/bin/env python3

import socket
import threading
import time
import json

from flask import Flask, render_template, redirect, request

app = Flask(__name__)

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

def cliente_connectado(conn,addr):
    with conn:
        print('Connected by', addr)
        id = str(conn.recv(1024))
        while True:
            data = int(conn.recv(1024))
            dados.setdefault(id,[]).append(data) 
            if not data:
                break

@app.route("/")
def rota_inicial():
    return render_template("index.html", dados = dados)

if __name__ == "__main__":
    dados = {}
    s = threading.Thread(target=servidor_tcp)
    s.start()
    app.run("0.0.0.0",port=8080) 
            