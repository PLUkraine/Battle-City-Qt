import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.1

import BattleCity 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MessageDialog {
        id: gameOverDialog
        title: "Game over!"
        text: "Try again?"
        standardButtons: StandardButton.No | StandardButton.Yes
        onYes: {
            // TODO restart game
            gameObj.createAndStartGame(":/levels/level1.json")
        }
        onNo: {
            Qt.quit()
        }
    }

    Game {
        id: gameObj
        anchors.fill: parent
        focus: true
        visible: true
        onGameOver: {
            gameOverDialog.visible = true
        }
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
