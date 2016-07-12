#include "resoursecontainer.h"

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

ResBag::ResBag()
{
    m_tileSprites[0] = QImage(":/sprites/air.png");
    m_tileSprites[1] = QImage(":/sprites/wall.png");
    m_tankSprite = QImage(":/sprites/tank.png");
    m_bulletSprite = QImage(":/sprites/bullet.png");

    // TODO read from the config file
    m_bulletSize = 1;
    m_bulletSpeed = 0.75;
    m_tankSize = 5;
    m_tileSize = 5;
    m_tankSpeed = 0.5;
    m_bulletDamage = 5;
    m_tankHealth = 5;

    m_tileHealth[0] = 0;
    m_tileHealth[1] = 5;
}
