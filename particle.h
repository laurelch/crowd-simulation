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
    void setGroup(int);
    int getGroup();
    void setDisease(qreal);
    qreal getDisease();
private:
    qreal x;
    qreal y;
    int group;
    qreal disease;
};

#endif // PARTICLE_H
