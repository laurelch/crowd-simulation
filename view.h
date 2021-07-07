#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QGraphicsEllipseItem>
class View : public QGraphicsView
{
    Q_OBJECT
    int particle_count=100;
    bool pause=true;
public:
    View(QWidget *parent=nullptr);
    ~View();
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void togglePause();
};

#endif // VIEW_H
