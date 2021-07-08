#include "particle.h"

Particle::Particle()
{
    setX(0);
    setY(0);
}

Particle::Particle(qreal x,qreal y)
{
    setX(x);
    setY(y);
}

qreal Particle::getX()
{
    return x;
}

void Particle::setX(qreal x)
{
    this->x = x;
}

qreal Particle::getY()
{
    return y;
}

void Particle::setY(qreal y)
{
    this->y = y;
}

void Particle::setGroup(int g)
{
    group = g;
}

int Particle::getGroup()
{
    return group;
}

void Particle::setDisease(qreal d)
{
    disease = d;
}

qreal Particle::getDisease()
{
    return disease;
}
