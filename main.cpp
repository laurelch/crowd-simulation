#include <QApplication>
#include "view.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    QGraphicsScene scene;
//    static const int PARTICLE_COUNT=100;
//    for(int particleNum=0;particleNum<PARTICLE_COUNT;++particleNum) {
//        QGraphicsEllipseItem *circleItem = new QGraphicsEllipseItem(QRect(rand()%600,rand()%600,10,10));
//        circleItem->setBrush(Qt::red);
//        scene.addItem(circleItem);
//    }
//    QGraphicsView view(&scene);
//    view.show();
//    return a.exec();

    QApplication a(argc,argv);
    View w;
    w.show();
    return a.exec();
}
