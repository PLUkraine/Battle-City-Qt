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
    title: qsTr("Battle City clone Qt edition")
    minimumHeight: 800
    minimumWidth: 1000
    maximumHeight: 800
    maximumWidth: 1000

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
                id: controlsLabel
                text: "Move: arrows\nShoot: space"
                font.pointSize: 13
            }

            ColumnLayout {
                Label {
                    text: "Health"
                    font.pointSize: 13
                }
                ProgressBar{
                    width: 100
                    id: healthBar
                    value: 0
                    maximumValue: 10
                }
            }
            ColumnLayout {
                Label {
                    text: "Enemies left"
                    font.pointSize: 13
                }
                ProgressBar{
                    width: 100
                    id: enemiesLeftBar
                    value: 0
                    maximumValue: 10
                }
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
                healthBar.value = h;
            });
            gameObj.enemyLeftChanged.connect(function(en) {
               enemiesLeftBar.value = en;
            });
            gameObj.gameStarted.connect(function (h, en) {
                healthBar.maximumValue = h;
                healthBar.value = h;
                enemiesLeftBar.maximumValue = en;
                enemiesLeftBar.value = en;
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
