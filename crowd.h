#ifndef CROWD_H
#define CROWD_H

#include <QGraphicsItem>
#include "particle.h"
class Crowd : public QGraphicsItem
{
public:
    Crowd();
    Crowd(int);
    ~Crowd();
    // QGraphicsItem interface
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setCount(int);
    int getCount();
    void setParticleStatus(int i,float*);
private:
    int count;
    QVector<Particle*> particles;
};

#endif // CROWD_H
