#include "view.h"
#include <iostream>
View::View(QWidget *parent)
    : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setScene(new QGraphicsScene);
    for(int particleNum=0;particleNum<particle_count;++particleNum) {
        QGraphicsEllipseItem *circleItem = new QGraphicsEllipseItem(QRect(rand()%600,rand()%600,10,10));
        circleItem->setBrush(Qt::red);
        scene()->addItem(circleItem);
    }
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
        std::cout<<"View::keyPressEvent space pressed. pause="<<pause<<std::endl;
        break;
    case Qt::Key_S:
        std::cout<<"View::keyPressEvent S pressed."<<std::endl;
        break;
    }
}

void View::togglePause()
{
    pause=!pause;
}
