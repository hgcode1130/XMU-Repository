import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.1
import EC20 1.0
import QtQuick.Dialogs 1.2
import MyBackend 1.0
import WorkerObject 1.0
import CallRecordModel 1.0

Window {
    id:rootwindow
    visible: true
    width: Screen.width
    height: Screen.height
    opacity: 1
    visibility: Window.FullScreen
    flags: Qt.BypassGraphicsProxyWidget | Qt.FramelessWindowHint
    title: "Phone App"
    Item {
      id: mainContainer
      width: rootwindow.width
      height: rootwindow.height
      anchors.centerIn: parent
    CallRecordModel{
    id:callRecordModel
    }

    Modelmessagedialog {
        id:messagedialog
        msgtext : "4G模组丢失，请插入模组"
    }
    Modelmessagedialog {
        id:simmessagedialog
        tipText : "未找到SIM卡，请检查插卡是否稳定"
    }

    function onTurn180(){
        mainContainer.rotation = 180
    }
    function onTurn0(){
        mainContainer.rotation = 0
    }

    Text {
      id: tip
      text: qsTr("电话")

      anchors.bottom: pNum.bottom
      anchors.bottomMargin: 130
      anchors.left: parent.left
      anchors.leftMargin: 20

      font.family: "Noto Sans CJK SC Regular"
      font.pixelSize: 80
    }

    TextField {
      id: pNum
      width: rootwindow.width-270
      height: rootwindow.height * 0.3
      readOnly: true
      anchors.top: rootwindow.top
      anchors.right: parent.right
      horizontalAlignment: Text.AlignRight
      font.family: "Noto Sans CJK SC Regular"
      font.pixelSize: rootwindow.height * 0.1
      background: Rectangle {
        color: "transparent"
      }
    }

    GridLayout {
        columns: 3
        width: pNum.width-100
        height: rootwindow.height-pNum.height-100
        anchors.top: pNum.bottom
        anchors.topMargin: 50
        anchors.left: pNum.left
        anchors.leftMargin: 50
        anchors.horizontalCenter: pNum.horizontalCenter

        property int buttonSize: 80

        RoundButton {
           id:nine
           radius: 5
           Text {
               text: "1";
               color: "#707070"
               font.family: "Noto Sans CJK SC Regular"
               font.pixelSize: rootwindow.width*0.021
             anchors.centerIn: parent
           }
           palette.button: "white";
           onClicked: {
             pNum.text += "1";
           }
           Layout.fillWidth: true
           Layout.fillHeight: true
        }

        RoundButton {
            radius: 5
            Text {
                text: "2";
                color: "#707070"
                font.family: "Noto Sans CJK SC Regular"
                font.pixelSize: rootwindow.width*0.021
              anchors.centerIn: parent
            }
           palette.button: "white";
           onClicked: {
            pNum.text += "2";
           }
           Layout.fillWidth: true
           Layout.fillHeight: true
        }
        RoundButton {
            radius: 5
            Text {
                text: "3";
                color: "#707070"
                font.family: "Noto Sans CJK SC Regular"
                font.pixelSize: rootwindow.width*0.021
              anchors.centerIn: parent
            }
             palette.button: "white";
             Layout.fillWidth: true
             Layout.fillHeight: true
             onClicked: {
               pNum.text += "3";
             }
           }
      RoundButton {
          radius: 5
          Text {
              text: "4";
              color: "#707070"
              font.family: "Noto Sans CJK SC Regular"
              font.pixelSize: rootwindow.width*0.021
            anchors.centerIn: parent
          }
            palette.button: "white";
            onClicked: {
              pNum.text += "4";
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
          }
      RoundButton {
          radius: 5
          Text {
              text: "5";
              color: "#707070"
              font.family: "Noto Sans CJK SC Regular"
              font.pixelSize: rootwindow.width*0.021
            anchors.centerIn: parent
          }
            palette.button: "white";
            onClicked: {
              pNum.text += "5";
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
          }
      RoundButton {
          radius: 5
          Text {
              text: "6";
              color: "#707070"
              font.family: "Noto Sans CJK SC Regular"
              font.pixelSize: rootwindow.width*0.021
            anchors.centerIn: parent
          }
            palette.button: "white";
            onClicked: {
              pNum.text += "6";
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
          }

      RoundButton {
          radius: 5
          Text {
              text: "7";
              color: "#707070"
              font.family: "Noto Sans CJK SC Regular"
              font.pixelSize: rootwindow.width*0.021
            anchors.centerIn: parent
          }
            palette.button: "white";
            onClicked: {
              pNum.text += "7";
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
          }
      RoundButton {
          radius: 5
          Text {
              text: "8";
              color: "#707070"
              font.family: "Noto Sans CJK SC Regular"
              font.pixelSize: rootwindow.width*0.021
            anchors.centerIn: parent
          }
            palette.button: "white";
            onClicked: {
              pNum.text += "8";
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
          }
      RoundButton {
          radius: 5
          Text {
              text: "9";
              color: "#707070"
              font.family: "Noto Sans CJK SC Regular"
              font.pixelSize: rootwindow.width*0.021
            anchors.centerIn: parent
          }
            palette.button: "white";
            onClicked: {
              pNum.text += "9";
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
          }
      RoundButton {
          id:starkey
          radius: 5
          palette.button: "white";
          onClicked: pNum.text += "*" ;
          Text {
            text: "*";
            color: "#707070"
            font.family: "Noto Sans CJK SC Regular"
            font.pixelSize: rootwindow.width*0.021
            anchors.centerIn: parent
          }
          Layout.fillWidth: true
          Layout.fillHeight: true
      }
      RoundButton {
          id:zerokey
          radius: 5
          Text {
              text: "0";
              color: "#707070"
              font.family: "Noto Sans CJK SC Regular"
              font.pixelSize: rootwindow.width*0.021
            anchors.centerIn: parent
          }
            palette.button: "white";
            onClicked: {
              pNum.text += "0";
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
          }

      RoundButton {
          id:poundkey
          radius: 5
          palette.button: "white";
          onClicked: pNum.text += "#" ;
          Text {
            text: "#";
            color: "#707070"
            font.family: "Noto Sans CJK SC Regular"
            font.pixelSize: rootwindow.width*0.021
            anchors.centerIn: parent
          }
          Layout.fillWidth: true
          Layout.fillHeight: true
      }

      Rectangle{
          id:exitButtonRe
          anchors.left: starkey.left
          anchors.leftMargin: 135
          width: exitButton.width
          height: exitButton.height
      Image {
        id: exitButton
        source: "qrc:/icon/icon/exit.png"
        width: rootwindow.width*0.035
        height: rootwindow.width*0.035
//        scale: 0.3
        MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit()
        }
        }

        Layout.fillWidth: true
        Layout.fillHeight: true
      }
      }

      Rectangle {
        id: callButtonRe
        anchors.left: zerokey.left
        anchors.leftMargin: 130
        width: callButton.width
        height: callButton.height

        Image {
          id: callButton
          source: "qrc:/icon/icon/CALL.png"
          width: rootwindow.width*0.035
          height: rootwindow.width*0.035

          MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("call clicked")
                popcall.number = pNum.text
                popcall.open()
                popcall.visible = true
                worker.call(pNum.text)
                callTimer.start()
            }
          }

          Timer {
            id: callTimer
            interval: 70000
            onTriggered: {
//              console.log("no anwser")
              popcall.close()
              worker.handUp()
            }
          }

          Layout.fillWidth: true
          Layout.fillHeight: true
        }
      }

      Rectangle{
          id:backButtonRe
          anchors.left: poundkey.left
          anchors.leftMargin: 130
          anchors.top: poundkey.bottom
          anchors.topMargin: 7
          width: backButton.width
          height: backButton.height
      Image {
        id: backButton
        source: "qrc:/icon/icon/back.png"
        width: rootwindow.width*0.035
        height: rootwindow.width*0.035
        MouseArea {
          anchors.fill: parent
          onClicked: {
          if(pNum.text.length > 0) {
            pNum.text = pNum.text.slice(0, pNum.text.length-1)
          }
          }
        }
        Layout.fillWidth: true
        Layout.fillHeight: true
      }
     }

   }

    Pop {
      id: popup
      width: parent.width
      height: parent.height
      padding: 0
    }


    signal sendanswer()
    signal nocarrier()
    signal popupnocarrier()
    signal sendNum(var num)

    Component.onCompleted: {
        if (isS5P6818) {
          console.log("Connecting signals...");
          lis3dh.turn180.connect(onTurn180);
          lis3dh.turn0.connect(onTurn0);
        } else {
          console.log("lis3dh is not available on this platform.");
        }
      phoneThread.sendanswer.connect(onSendAnswerReceived)
      phoneThread.behundup.connect(onBehundupReceived)
      phoneThread.senlost.connect(onSendSimLostSlot)
      phoneThread.sendmodellost.connect(onSendModelLostSlot)
      phoneThread.sendnum.connect(function(num) {
        Qt.callLater(function() {
          onSendNumed(num);
        });
        });
    }

    function onSendSimLostSlot(){
        simmessagedialog.openMsg()
    }

    function onSendModelLostSlot(){
        messagedialog.openMsg()
    }

    function onSendNumed(num) {
//      console.log("sendNum signal received")
        popup.open()
        sendNum(num)
    }

    function onSendAnswerReceived() {
      console.log("Answer signal received")
        callTimer.running = false
        popcall.open()
        sendanswer()
    }

    function onBehundupReceived() {
//      console.log("Hang up signal received")
        nocarrier()
        popupnocarrier()
    }

    PopCall {
      id: popcall
      width: parent.width
      height: parent.height
      padding: 0

    }
    WorkerObject {
      id: worker
    }

    EC20{
        id:ec20
    }

    MyBackend {
      id: backend
    }
  }
}
