#!/usr/bin/env python3

import socket
import threading
import time
import json
import time
import signal
import sys

from protocolo import protocolo
from tcp_lib import TCP_SERVER
     

if __name__ == "__main__":
    tcp_server = TCP_SERVER("http://192.168.0.153:8080","",65432)
    
    web_conn = threading.Thread(target=tcp_server.verifica_estado)
    web_conn.start()
    tcp_server.start()