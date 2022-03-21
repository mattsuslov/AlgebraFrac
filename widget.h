#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "canvas.h"

class Widget : public QGraphicsView
{
public:
    Widget();
    ~Widget();

private:
    QGraphicsScene scene;
    Canvas cvs;
};
#endif // WIDGET_H
