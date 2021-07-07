#ifndef PARTICLE_H
#define PARTICLE_H
#include <QtGlobal>

class Particle
{
public:
    Particle();
    Particle(qreal,qreal);
    qreal getX();
    void setX(qreal);
    qreal getY();
    void setY(qreal);
private:
    qreal x;
    qreal y;
};

#endif // PARTICLE_H
