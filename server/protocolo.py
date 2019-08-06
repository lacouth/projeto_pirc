import json
import requests

def protocolo(cliente, conn, msg,dados, conexoes,WEB_SERVER):
    
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
                # print(WEB_SERVER,json.dumps(dados))
            try:

                    requests.post(WEB_SERVER+"/upload",json=json.dumps(dados))
            except:
                print("Erro de comunicação WEB")
        elif(msg[0] == "DEVLST"):
            sendDEVLST(conn,conexoes)
        elif(msg[0] == "GETMEAS"):
            sendMEAS(conn,msg[1],dados)
        elif(msg[0] == "TURN"):
            if msg[1] in conexoes:
                sendLED(conexoes[msg[1]],msg[2])
                sendOK(conn)
        else:
            sendERROR(conn)
    except:
        sendERROR(conn)

def sendFrq(conn,valor):
    conn.sendall(str("FRQ " + str(valor)).encode())

def sendOK(conn):
    conn.sendall("+OK".encode())

def sendLED(conn, led_estado):
    conn.sendall(("+LED "+str(led_estado)).encode())

def waitMessage(conn):
    return str(conn.recv(1024).decode("utf-8")).split()

def sendDEVLST(conn, conexoes):
    if(len(conexoes)>0):
        resp = ""
        for id in conexoes:
            resp += "+ID " + str(id)
        conn.sendall(resp.encode())
    else:
        sendERROR(conn)

def sendMEAS(conn,id,dados):
    if id in dados :
        d = dados[id][len(dados[id])-1]
        conn.sendall(("+DATA "+str(d)).encode())
    else:
        sendERROR(conn)

def sendERROR(conn):
    conn.sendall("+ERROR".encode())