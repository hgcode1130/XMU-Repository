import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.1
import EC20 1.0
//import PhoneThread 1.0
import MyBackend 1.0
Popup {
    id: popcall
     property string number
     onVisibleChanged: if(!visible) close()
     Rectangle {
     id:popcallrectangle
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
             mainContainer.sendanswer.connect(onSendAnswerReceive)
             mainContainer.nocarrier.connect(onBehundupReceive)
             console.log("Connecting signals...");
             lis3dh.turn180.connect(onPopCallTurn180);
             lis3dh.turn0.connect(onPopCallTurn0);
         }else{
             rootwindow.sendanswer.connect(onSendAnswerReceive)
             rootwindow.nocarrier.connect(onBehundupReceive)
             console.log("lis3dh is not available on this platform.");
         }
     }

     function onPopCallTurn180(){
        popcallrectangle.rotation = 180
     }

     function onPopCallTurn0(){
        popcallrectangle.rotation = 0
     }

     function onSendAnswerReceive(){
         handupbtn.Layout.alignment = Qt.AlignHCenter;
         timerforcall.visible = true
         timercall.running = true
     }

     function onBehundupReceive(){
         console.log("popcall close")
         popcall.close()
         timercall.running = false
         timercall.elapsed = 0;
         timerforcall.visible = false
     }

     Timer {
       running: false
       repeat: true
       property int elapsed: 0
       id: timercall
       interval: 1000
       onTriggered: {
         timercall.elapsed += timercall.interval
           console.log(timercall.elapsed)
       }
     }

     ColumnLayout {
     anchors.fill: parent
     Layout.fillWidth: true
     Layout.fillHeight: true
     Layout.leftMargin: 0
     Layout.topMargin: 0

     Text {
         id:callnum
         opacity: 1
         Layout.alignment: Qt.AlignHCenter
         font.pixelSize: 70
         text: number
         color: "#ffffff"
     }
     Text {
         opacity: 1
         id:timerforcall
         function formatTime(time){
           let minutes = Math.floor(time / 1000 / 60);
           let seconds = ((time / 1000 % 60)).toFixed(0)
           return minutes + ":" + (seconds < 10 ? "0" : "") + seconds
         }

       visible: false
       Layout.alignment: callnum.bottom|Qt.AlignHCenter
       font.family: "Noto Sans CJK SC Regular"
       font.pixelSize: 35
       color: "#ffffff"
       text: formatTime(timercall.elapsed)
     }
       Rectangle{
           id:backButtonRe
           color: "transparent"
           Layout.alignment:Qt.AlignHCenter
           width: handupbtn.width
           height: handupbtn.height
       Image {
         id: handupbtn
         opacity: 1
         source: "qrc:/icon/icon/handup.png"
         width: rootwindow.width*0.12
         height: rootwindow.width*0.12
         y: 88
         MouseArea {
           anchors.fill: parent
           onClicked: {
               console.log(handupbtn.x)
               console.log(handupbtn.y)
               console.log("handup")
               popcall.close()
               timercall.running = false
               timercall.elapsed = 0;
               timerforcall.visible = false
               worker.handUp()
           }
         }
         Layout.fillWidth: true
         Layout.fillHeight: true
       }
      }
     }
     }
}

