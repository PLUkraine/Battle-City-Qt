#ifndef RESOURSECONTAINER_H
#define RESOURSECONTAINER_H

#include <QImage>
#include <QString>

/**
 * @brief The ResourseContainer class - singleton for storing images and constants needed for
 * entities creation
 */
class ResBag
{
public:
    static ResBag& get();

    QImage* tankSprite();

    QImage* bulletSprite();

    QImage* tilesSptites();

    ResBag(const ResBag&) = delete;
    void operator=(const ResBag&) = delete;

    qreal tankSize() const;

    qreal tileSize() const;

    qreal bulletSize() const;

    qreal tankSpeed() const;

    qreal bulletSpeed() const;

    qreal bulletDamage() const;

    qreal tankHealth() const;

    qreal* tileHealth();

    qreal weaponCooldown() const;

    bool *tileSolidness();

private:
    QImage m_tileSprites[2];
    QImage m_tankSprite;
    QImage m_bulletSprite;

    qreal m_tankSize, m_tileSize, m_bulletSize;
    qreal m_tankSpeed, m_bulletSpeed;
    qreal m_bulletDamage;
    qreal m_tankHealth;
    qreal m_tileHealth[2];
    bool m_tileSolidness[2];

    qreal m_weaponCooldown;

    ResBag();
    void readConfigs();
    void handleError(QString message);
};

#endif // RESOURSECONTAINER_H
