import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import connection 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: "Cliente local"
    Connection{
        id: connection
    }

    Column {
        id: column
        anchors.margins: 10
        anchors.fill: parent
        spacing: 10

        Row {
            id: row
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: 5
            Label {
                id: label
                width: 70
                height: 17
                text: qsTr("Servidor")
                anchors.verticalCenter: parent.verticalCenter
            }

            TextField {
                id: server_addr
                text: qsTr("")
                anchors.verticalCenter: parent.verticalCenter
            }

            Label {
                id: label1
                text: qsTr("Porta")
                anchors.verticalCenter: parent.verticalCenter
            }

            TextField {
                id: server_port
                text: qsTr("")
                anchors.verticalCenter: parent.verticalCenter
            }

            Button {
                id: btn_connection
                text: qsTr("Conectar")
                highlighted: true
                Material.background: Material.Teal
                onClicked: conectar()
            }
        }

        Row {
            id: row1
            width: 200
            anchors.horizontalCenter: parent.horizontalCenter
            Label {
                id: label2
                width: 70
                height: 17
                text: qsTr("Status: ")
                anchors.verticalCenter: parent.verticalCenter
            }
            Label {
                id: label3
                width: 70
                height: 17
                text: qsTr("Desconectado")
                anchors.verticalCenter: parent.verticalCenter
            }

        }

    }

    /*-----------Funções----------*/

      function conectar(){
          connection.conectarServidor(server_addr.text, server_port.text)
      }

}











/*##^## Designer {
    D{i:2;anchors_width:200}
}
 ##^##*/
