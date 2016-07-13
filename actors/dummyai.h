#ifndef DUMMYAI_H
#define DUMMYAI_H
#include "actor.h"

#include <random>

class DummyAI : public Actor
{
public:
    DummyAI(QObject *parent = 0);

    void makeMove(Board *board, EntitiesBag *bag, Tank *tank);
protected:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<double> dist;

    int m_togo;
};

#endif // DUMMYAI_H
