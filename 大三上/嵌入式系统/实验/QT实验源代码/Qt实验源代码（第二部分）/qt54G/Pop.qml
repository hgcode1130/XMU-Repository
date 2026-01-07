import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.1
import EC20 1.0
//import PhoneThread 1.0
import MyBackend 1.0
Popup {
    id: popup
     property string number
     onVisibleChanged: if(!visible) close()
     Rectangle {
     id:poprectangle
     anchors.fill: parent
     Image {
       source: "qrc:/icon/icon/background.jpg"
       anchors.fill: parent
       opacity: 1
       Rectangle{
       anchors.fill: parent
       color: "#000000"
       opacity: 0.65
       }
     }

     Component.onCompleted: {
         if(isS5P6818){
            mainContainer.sendNum.connect(onSendNum)
            mainContainer.popupnocarrier.connect(onClosed)
             console.log("Connecting signals...");
             lis3dh.turn180.connect(onPopTurn180);
             lis3dh.turn0.connect(onPopTurn0);
         }else{
             rootwindow.sendNum.connect(onSendNum)
             rootwindow.popupnocarrier.connect(onClosed)
             console.log("lis3dh is not available on this platform.");
         }
     }

     function onPopTurn180(){
        poprectangle.rotation = 180
     }

     function onPopTurn0(){
        poprectangle.rotation = 0
     }

     function onSendNum(num) {
         number = num
     }

     function onClosed() {
         console.log("closepop")
         popup.close()
         timer.running = false
         timer.elapsed = 0;
         answerButton.visible = true;
         handupButton.Layout.alignment = Qt.AlignRight;
         timeforcall.visible = false;
     }

     Timer {
       running: false
       repeat: true
       property int elapsed: 0
       id: timer
       interval: 1000
       onTriggered: {
         timer.elapsed += timer.interval
           console.log(timer.elapsed)
       }
     }

     ColumnLayout {
     anchors.fill: parent
     Layout.fillWidth: true
     Layout.fillHeight: true
     Layout.leftMargin: 0
     Layout.topMargin: 0

     Text {
         id:phonenum
         opacity: 1
         Layout.alignment: Qt.AlignHCenter
         font.pixelSize: 70
         text: number
         color: "#ffffff"
     }
     Text {
         id:timeforcall
         opacity: 1
         function formatTime(time) {
           let minutes = Math.floor(time / 1000 / 60)
           let seconds = ((time / 1000 % 60)).toFixed(0)
           return minutes + ":" + (seconds < 10 ? "0" : "") + seconds
         }

       visible: false
       Layout.alignment: phonenum.bottom|Qt.AlignHCenter
       font.family: "Noto Sans CJK SC Regular"
       font.pixelSize: 35
       color: "#ffffff"
       text: formatTime(timer.elapsed)
     }

     RowLayout {
       id:buttonlayout
       Layout.alignment: Qt.AlignHCenter|Qt.AlignBottom
       spacing: 300
       Layout.leftMargin: 0
       Layout.bottomMargin: 80

       Rectangle{
           id:handupButton
           color: "transparent"
           Layout.alignment:Qt.AlignRight
           width: handupIcon.width
           height: handupIcon.height
       Image {
         id: handupIcon
         opacity: 1
         source: "qrc:/icon/icon/handup.png"
         width: rootwindow.width*0.12
         height: rootwindow.width*0.12
         MouseArea {
           anchors.fill: parent
           onClicked: {
               console.log("handup")
               popup.close()
               worker.handUp()
               timer.running = false
               timer.elapsed = 0;
               answerButton.visible = true;
               handupButton.Layout.alignment = Qt.AlignRight;
               timeforcall.visible = false;
           }
         }
         Layout.fillWidth: true
         Layout.fillHeight: true
       }
      }

       Rectangle{
           id:answerButton
           color: "transparent"
           Layout.alignment:Qt.AlignLeft
           width: answerIcon.width
           height: answerIcon.height
       Image {
         id: answerIcon
         opacity: 1
         source: "qrc:/icon/icon/CALL.png"
         width: rootwindow.width*0.12
         height: rootwindow.width*0.12
         MouseArea {
           anchors.fill: parent
           onClicked: {
               console.log("answer")
               answerButton.visible = false;
               handupButton.Layout.alignment = Qt.AlignHCenter;
//               handupButton.x = 83
//               handupIcon.x = 83
               worker.answerCall()
               timeforcall.visible = true
               timer.running = true
           }
         }
         Layout.fillWidth: true
         Layout.fillHeight: true
       }
      }
     }
     }
     }
}

