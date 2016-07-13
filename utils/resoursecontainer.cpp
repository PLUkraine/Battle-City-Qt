#include "resoursecontainer.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <iostream>

ResBag &ResBag::get()
{
    static ResBag container;
    return container;
}

QImage *ResBag::tankSprite()
{
    return &m_tankSprite;
}

QImage *ResBag::bulletSprite()
{
    return &m_bulletSprite;
}

QImage *ResBag::tilesSptites()
{
    return m_tileSprites;
}

qreal ResBag::tankSize() const
{
    return m_tankSize;
}

qreal ResBag::tileSize() const
{
    return m_tileSize;
}

qreal ResBag::bulletSize() const
{
    return m_bulletSize;
}

qreal ResBag::tankSpeed() const
{
    return m_tankSpeed;
}

qreal ResBag::bulletSpeed() const
{
    return m_bulletSpeed;
}

qreal ResBag::bulletDamage() const
{
    return m_bulletDamage;
}

qreal ResBag::tankHealth() const
{
    return m_tankHealth;
}

qreal *ResBag::tileHealth()
{
    return m_tileHealth;
}

qreal ResBag::weaponCooldown() const
{
    return m_weaponCooldown;
}

bool *ResBag::tileSolidness()
{
    return m_tileSolidness;
}

ResBag::ResBag()
{
    m_tileSprites[0] = QImage(":/sprites/air.png");
    m_tileSprites[1] = QImage(":/sprites/wall.png");
    m_tankSprite = QImage(":/sprites/tank_sprites.png");
    m_bulletSprite = QImage(":/sprites/bullet.png");

    readConfigs();
}

void ResBag::readConfigs()
{
    QFile file(":/config/gameconfig.json");
    if (!file.exists())
        handleError("File doesn't exist!");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray val = file.readAll();
    file.close();

    QJsonParseError er;
    QJsonObject root = QJsonDocument::fromJson(val, &er).object();
    if (er.error != QJsonParseError::NoError)
        handleError("Error while reading config: " + er.errorString());

    // read tank info
    QJsonObject tank = root["tank"].toObject();
    m_tankSize = tank["size"].toDouble();
    m_tankHealth = tank["health"].toInt();
    m_tankSpeed = tank["speed"].toDouble();

    // read tile info
    QJsonObject tile = root["tile"].toObject();
    m_tileSize = tile["size"].toDouble();
    QJsonArray data = tile["health"].toArray();
    for (int i=0; i<data.count(); ++i) {
        m_tileHealth[i] = data[i].toInt();
    }
    data = tile["solid"].toArray();
    for (int i=0; i<data.count(); ++i) {
        m_tileSolidness[i] = data[i].toBool();
    }

    // read bullet info
    QJsonObject bullet = root["bullet"].toObject();
    m_bulletSize = bullet["size"].toDouble();
    m_bulletSpeed = bullet["speed"].toDouble();
    m_bulletDamage = bullet["damage"].toInt();

    // read weapon info
    QJsonObject stdWeapon = root["standardWeapon"].toObject();
    m_weaponCooldown = stdWeapon["cooldown"].toInt();

}

void ResBag::handleError(QString message)
{
    std::cerr << message.toStdString();
    exit(1);
}
