#!/usr/bin/env python3

import socket

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 65432        # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    while(True):
        msg = input(">> ").upper()
        if(msg == "EXIT"):
            s.close()
            exit(0)
        s.sendall(msg.encode())
        data = s.recv(1024)
        print(data.decode('utf-8'))