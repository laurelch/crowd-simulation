#include <QPainter>
#include "crowd.h"
#include <iostream>
using namespace std;

Crowd::Crowd()
{
    Particle* particle;
    setCount(10);
    for(int i=0;i<getCount();++i){
        particle = new Particle(rand()%600,rand()%600);
        if(i<getCount()/2){
            particle->setGroup(0);
        }else{
            particle->setGroup(1);
        }
        particle->setDisease(float(rand()%100)*0.01);
        cout<<"particle disease="<<particle->getDisease()<<endl;
        particles.push_back(particle);
//        cout<<"particle="<<particle<<", x="<<particle->getX()<<", y="<<particle->getY()<<endl;
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
    for(Particle* particle: qAsConst(particles)){
        painter->setBrush(QColor(255,0,0));
        int group=particle->getGroup();
        if(group==1){
            painter->setBrush(QColor(0,0,255));
        }
//        cout<<"particle="<<particle<<"x="<<particle->getX()<<", y="<<particle->getY()<<endl;
        painter->drawEllipse(QRect(particle->getX(),particle->getY(),10,10));

        // plot disease
        qreal disease=particle->getDisease();
        painter->setBrush(QColor(255*disease,255*disease,255*disease));
        painter->drawEllipse(QRect(particle->getX()+700,particle->getY(),10,10));
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
