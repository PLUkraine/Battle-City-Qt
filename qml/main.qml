import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.1
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import BattleCity 1.0
import "/js/callbacks.js" as Callbacks

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
                onClicked: Callbacks.createGame(gameObj, gameErrorMessage);
            }
            Button {
                text: "Pause/resume game"
                onClicked: gameObj.pauseOrResumeGame();
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
        onYes:
            Callbacks.createGame(gameObj, gameErrorMessage);
        onNo:
            Qt.quit();
        onAccepted:
            Callbacks.createGame(gameObj, gameErrorMessage);
        onRejected:
            Qt.quit();
    }
    MessageDialog {
        id: victoryDialog
        title: "You won!"
        text: "Good job! Want to try again?"
        standardButtons: StandardButton.No | StandardButton.Yes
        onYes:
            Callbacks.createGame(gameObj, gameErrorMessage);
        onNo:
            Qt.quit();
        onAccepted:
            Callbacks.createGame(gameObj, gameErrorMessage);
        onRejected:
            Qt.quit();
    }
    MessageDialog {
        id: gameErrorMessage
        title: "Error occured"
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
        onGameOver:
            gameOverDialog.visible = true;
        onVictory:
            victoryDialog.visible = true;
        Component.onCompleted: Callbacks.connectGameToBars(gameObj, healthBar, enemiesLeftBar)
    }
}
