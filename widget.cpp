#include "widget.h"

Widget::Widget()
{
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    setFrameStyle(0);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(1000, 700);


    setSceneRect(QRect(0, 0, 1000, 700));
    setScene(&scene);


    scene.addItem(&cvs);
    cvs.setPos(0, 0);
}

Widget::~Widget()
{

}

