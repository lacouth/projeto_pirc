#!/usr/bin/env python3

import socket
import threading
import time
import json
import time
import signal
import sys

from tcp_lib import servidor_tcp, verifica_estado, cliente_connectado
from protocolo import protocolo
     

if __name__ == "__main__":
    WEB_SERVER = "http://192.168.0.153:8080"
    HOST = ''  
    PORT = 65432
    dados = {}
    conexoes = {}
    threads = []
    
    web_conn = threading.Thread(target=verifica_estado,args=(WEB_SERVER,conexoes))
    web_conn.start()
    servidor_tcp(threads,dados,conexoes,HOST,PORT,WEB_SERVER)