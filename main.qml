import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.1
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import BattleCity 1.0

Window {
    visible: true
    width: 1000
    height: 800
    title: qsTr("Battle City clone Qt edition I bet no one read this lol")
    minimumHeight: 400
    minimumWidth: 600

    Rectangle  {
        id: uipanel
        anchors.right: parent.right
        width: 200
        ColumnLayout {
            anchors.fill: parent
            spacing: 6
            Button {
                text: "Start new game"
                onClicked: gameObj.createAndStartGame(":/levels/level1.json")
            }
            Button {
                text: "Pause/resume game"
                onClicked: gameObj.pauseOrResumeGame()
            }
            Label {
                id: healthLabel
                text: "Health: 0"
                font.pointSize: 13
            }
            Label {
                id: enemiesLeftLabel
                text: "Enemies left: 0"
                font.pointSize: 13
            }
        }
    }



    MessageDialog {
        id: gameOverDialog
        title: "Game over!"
        text: "You lost! Try again?"
        standardButtons: StandardButton.No | StandardButton.Yes
        onYes: {
            gameObj.createAndStartGame(":/levels/level1.json");
        }
        onNo: {
            Qt.quit();
        }
        onAccepted:
            gameObj.createAndStartGame(":/levels/level1.json");
        onRejected:
            Qt.quit();
    }
    MessageDialog {
        id: victoryDialog
        title: "You won!"
        text: "Good job! Want to try again?"
        standardButtons: StandardButton.No | StandardButton.Yes
        onYes: {
            gameObj.createAndStartGame(":/levels/level1.json");
        }
        onNo: {
            Qt.quit();
        }
        onAccepted:
            gameObj.createAndStartGame(":/levels/level1.json");
        onRejected:
            Qt.quit();
    }

    Game {
        id: gameObj
        anchors {
            top: parent.top
            left: parent.left
            right: uipanel.left
            bottom: parent.bottom
        }
        focus: true
        visible: true
        onGameOver: {
            gameOverDialog.visible = true;
        }
        onVictory: {
            victoryDialog.visible = true;
        }
        Component.onCompleted: {
            gameObj.playerHealthChanged.connect(function(h) {
                healthLabel.text = "Health: "+h;
            });
            gameObj.enemyLeftChanged.connect(function(en) {
               enemiesLeftLabel.text = "Enemies left: " + en;
            });
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
