#include <iostream>
#include "view.h"
#include "crowd.h"

View::View(QWidget *parent)
    : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setScene(new QGraphicsScene);
    setStepCount(0);
    setPauseCondition(1);
//    for(int particleNum=0;particleNum<getParticleCount();++particleNum) {
//        QGraphicsEllipseItem *circleItem = new QGraphicsEllipseItem(QRect(rand()%600,rand()%600,10,10));
//        circleItem->setBrush(QColor(255,0,0));
//        scene()->addItem(circleItem);
//    }
    Crowd *crowd = new Crowd();
    scene()->addItem(crowd);
    setAlignment(Qt::AlignTop|Qt::AlignLeft);
    scene()->setSceneRect(QRect(0,0,1250,650));
}

View::~View()
{
    delete scene();
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
            togglePause();
            std::cout<<"View::keyPressEvent space pressed. pause="<<getPauseCondition()<<std::endl;
            break;
        case Qt::Key_S:
            incrementStep();
            std::cout<<"View::keyPressEvent S pressed. step="<<getStepCount()<<std::endl;
            break;
        case Qt::Key_R:
            restart();
            std::cout<<"View::keyPressEvent R pressed. step="<<getStepCount()<<std::endl;
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

void View::restart()
{
    setStepCount(0);
}

void View::setPauseCondition(int p)
{
    this->pause = p;
}

void View::togglePause()
{
    pause = -pause;
}

int View::getPauseCondition()
{
    return pause;
}
