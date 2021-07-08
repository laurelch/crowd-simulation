#ifndef PARTICLE_H
#define PARTICLE_H
#include <iostream>
#include <QList>
class Particle
{
public:
    Particle();
    Particle(float,float);
    ~Particle();
    float getX();
    void setX(float);
    float getY();
    void setY(float);
    float getDirection();
    void setDirection(float,float);
    void setGroup(int);
    int getGroup();
    void setDisease(float);
    float getDisease();
    void setStatus(float,float,float,float,int,float);
    void setStatus(float*);
    void appendHistory();
private:
    float x;
    float y;
    int group;
    float disease;
    QList<float*> history;
};

#endif // PARTICLE_H
