#include <vector>
#include "particle.h"
using namespace std;
Particle::Particle()
{
    setX(0);
    setY(0);
}

Particle::Particle(float x,float y)
{
    setX(x);
    setY(y);
}

Particle::~Particle()
{
}

float Particle::getX()
{
    return x;
}

void Particle::setX(float x)
{
    this->x = x;
}

float Particle::getY()
{
    return y;
}

void Particle::setY(float y)
{
    this->y = y;
}

float Particle::getDirection()
{
    return 0;
}

void Particle::setDirection(float dx,float dy)
{
}

void Particle::setGroup(int g)
{
    group = g;
}

int Particle::getGroup()
{
    return group;
}

void Particle::setDisease(float d)
{
    disease = d;
}

float Particle::getDisease()
{
    return disease;
}

void Particle::setStatus(float x,float y,float dx,float dy,int group,float dss)
{
    setX(x);
    setY(y);
    setDirection(dx,dy);
    setGroup(group);
    setDisease(dss);
    appendHistory();
    cout<<history.size()<<endl;
}

void Particle::setStatus(float* status)
{
    float *f;
    f=status;
    setX(*f);
    setY(*(f+1));
    setDirection(*(f+2),*(f+3));
    setGroup(int(*(f+4)));
    setDisease(*(f+5));
    appendHistory();
    cout<<history.size()<<endl;
}

void Particle::appendHistory()
{
    float* fp;
    float status[5]={getX(),getY(),getDirection(),float(getGroup()),getDisease()};
    fp = status;
    history.push_back(fp);
}
