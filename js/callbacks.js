function createGame(gameObj, errorMessagebox) {
    gameObj.createAndStartGame(":/levels/level1.json");

    switch (gameObj.getLastError()) {
    case gameObj.NO_ERROR:
        break;
    case gameObj.LEVEL_NOT_FOUND:
        errorMessagebox.text = "Level's missing!";
        errorMessagebox.visible = true;
        break;
    case gameObj.LEVEL_NOT_FOUND:
        errorMessagebox.text = "Level's corrupted!";
        errorMessagebox.visible = true;
        break;
    }
}

function connectGameToBars(gameObj, healthBar, enemiesLeftBar) {
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
