import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.2
import QtGStreamer 1.0
import QtQuick.Controls 2.2;
Item {
    id: window
    //visible: true
    width: 640
    height: 480
    //title: qsTr("Hello World")
    anchors.fill: parent;
    VideoItem{
        anchors.fill: parent;
        surface: id_camera.VideoSurface();

    }
    Row{
        width: parent.width;
    Button{
        text : qsTr("replay");
        onClicked: {
            id_camera.Replay();
        }
    }
    Button{
        text:qsTr("set empty url");
        onClicked: {
            id_camera.Reset();
        }
    }
    }


//    InputPanel {
//        id: inputPanel
//        z: 99
//        x: 0
//        y: window.height
//        width: window.width

//        states: State {
//            name: "visible"
//            when: inputPanel.active
//            PropertyChanges {
//                target: inputPanel
//                y: window.height - inputPanel.height
//            }
//        }
//        transitions: Transition {
//            from: ""
//            to: "visible"
//            reversible: true
//            ParallelAnimation {
//                NumberAnimation {
//                    properties: "y"
//                    duration: 250
//                    easing.type: Easing.InOutQuad
//                }
//            }
//        }
//    }
}
