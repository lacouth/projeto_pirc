# gunicorn -w 4 --worker-class eventlet --bind 0.0.0.0:8080 web_server:app

from flask import Flask, render_template, redirect, request
from flask_socketio import SocketIO, emit
from flask_cors import CORS
import json
import eventlet 

eventlet.monkey_patch() 

app = Flask(__name__)
socketio = SocketIO(app)
socketio = SocketIO(app,async_mode = 'eventlet')

CORS(app)
dados = {}
estado = {}
change = 0

@app.route("/")
def rota_inicial():
    
    return render_template("index.html")

@app.route("/get")
def rota_getDados():
    return json.dumps(dados)

@app.route("/upload", methods=["POST"])
def rota_upload():
    
    dados = request.get_json()
    socketio.emit("atualiza", dados)
    return "200"

@app.route("/get_estado", methods=["GET"])
def rota_estado():
    global change, estado
    if change == 1:
        change = 0
        return json.dumps(estado)
    return "{}"
@socketio.on("ligar")
def socket_ligar(id):
    global change, estado
    if id in estado:
        if estado[id] == 0 :
            estado[id] = 1
            change = 1
    else:
        estado[id] = 1
    

@socketio.on("desligar")
def socket_desligar(id):
    global change, estado
    if id in estado:
        if estado[id] == 1 :
            estado[id] = 0
            change = 1
    else:
        estado[id] = 0


if __name__ == "__main__":
    
    app.run("0.0.0.0",port=8080)  
    