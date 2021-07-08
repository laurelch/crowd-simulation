#include <QPainter>
#include "crowd.h"
using namespace std;

Crowd::Crowd()
{
    setCount(10);
    Particle* particle;
    for(int i=0;i<getCount();++i){
        particle = new Particle(rand()%600,rand()%600);
        if(i<getCount()/2){
            particle->setGroup(0);
        }else{
            particle->setGroup(1);
        }
        float disease = rand()%100*0.01;
        particle->setDisease(disease);
        //cout<<"particle disease="<<particle->getDisease()<<"=>"<<disease<<endl;
        particles.push_back(particle);
        //cout<<"particle="<<particle<<", x="<<particle->getX()<<", y="<<particle->getY()<<endl;
    }
}

Crowd::Crowd(int count)
{
    setCount(count);
    Particle* particle;
    for(int i=0;i<getCount();++i){
        particle = new Particle(rand()%600,rand()%600);
        if(i<getCount()/2){
            particle->setGroup(0);
        }else{
            particle->setGroup(1);
        }
        float disease = rand()%100*0.01;
        particle->setDisease(disease);
        //cout<<"particle disease="<<particle->getDisease()<<"=>"<<disease<<endl;
        particles.push_back(particle);
        //cout<<"particle="<<particle<<", x="<<particle->getX()<<", y="<<particle->getY()<<endl;
    }
}

Crowd::~Crowd()
{
    Particle* particle;
    foreach(particle,particles)
        delete particle;
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

void Crowd::setParticleStatus(int index,float* status)
{
    particles[index]->setStatus(status);
}
