#include <iostream>
#include "view.h"
#include "crowd.h"

View::View(QWidget *parent)
    : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setScene(new QGraphicsScene);
    setParticleCount(100);
    setStepCount(0);
//    for(int particleNum=0;particleNum<getParticleCount();++particleNum) {
//        QGraphicsEllipseItem *circleItem = new QGraphicsEllipseItem(QRect(rand()%600,rand()%600,10,10));
//        circleItem->setBrush(QColor(255,0,0));
//        scene()->addItem(circleItem);
//    }
    Crowd *crowd = new Crowd();
    scene()->addItem(crowd);
    setAlignment(Qt::AlignTop|Qt::AlignLeft);
    scene()->setSceneRect(QRect(0,0,600,600));
}

View::~View()
{
    delete scene();
}

int View::getParticleCount(){
    return particle_count;
}

void View::setParticleCount(int c){
    this->particle_count = c;
}

void View::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
    if(event->isAccepted()){
        return;
    }
    const qreal factor = 1.1;
    if(event->angleDelta().y()>0){
        scale(factor,factor);
    }else{
        scale(1/factor,1/factor);
    }
    event->accept();
}

void View::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) {
        return;
    }
    switch(event->key()) {
        case Qt::Key_Space:
            std::cout<<"View::keyPressEvent space pressed."<<std::endl;
            break;
        case Qt::Key_S:
            incrementStep();
            std::cout<<"View::keyPressEvent S pressed. step="<<getStepCount()<<std::endl;
            break;
    }
}

void View::setStepCount(int s)
{
    this->step_count = s;
}

void View::incrementStep()
{
    step_count++;
}

int View::getStepCount()
{
    return step_count;
}
