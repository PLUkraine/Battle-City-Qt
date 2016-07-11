import QtQuick 2.5
import QtQuick.Window 2.2
import BattleCity 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Game {
        anchors.fill: parent

        visible: true
    }

//    MainForm {
//        Game {

//        }

//        anchors.fill: parent
//        mouseArea.onClicked: {
//            Qt.quit();
//        }
//    }
}
