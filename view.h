#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QGraphicsEllipseItem>
class View : public QGraphicsView
{
    Q_OBJECT

public:
    View(QWidget *parent=nullptr);
    ~View();
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void setPauseCondition(int);
    void togglePause();
    int getPauseCondition();
    void setStepCount(int);
    void incrementStep();
    int getStepCount();
    void restart();

private:
    int particle_count;
    int step_count;
    int pause;
};

#endif // VIEW_H
