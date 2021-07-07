#include <QPainter>
#include "crowd.h"
#include <iostream>
using namespace std;

Crowd::Crowd()
{
    Particle* particle;
    setCount(100);
    for(int i=0;i<getCount();++i){
        particle = new Particle(rand()%600,rand()%600);
        particles.push_back(particle);
        cout<<"particle="<<particle<<", x="<<particle->getX()<<", y="<<particle->getY()<<endl;
    }
}

QRectF Crowd::boundingRect() const
{
    return QRectF(0,0,10,10);
}

void Crowd::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setCosmetic(true);
    painter->setPen(pen);
//    for(int i=0;i<10;++i){
//        painter->setBrush(QColor(255,0,0));
//        painter->drawEllipse(QRect(rand()%600,rand()%600,10,10));
//    }
    for(Particle* particle: qAsConst(particles)){
        painter->setBrush(QColor(255,0,0));
//        cout<<"particle="<<particle<<"x="<<particle->getX()<<", y="<<particle->getY()<<endl;
        painter->drawEllipse(QRect(particle->getX(),particle->getY(),10,10));
    }
}

void Crowd::setCount(int n)
{
    count = n;
}

int Crowd::getCount()
{
    return count;
}
