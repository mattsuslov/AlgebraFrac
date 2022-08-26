#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include "complex.h"
#include <cmath>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class Canvas : public QGraphicsItem
{
public:
    Canvas();

    QRectF boundingRect() const override {
        return QRectF(0, 0, width_, height_);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        pressed_ = QVector2D(event->pos());
    }
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
        if ((QVector2D(event->pos()) - pressed_).length() >= 10) {
            move_ = true;
            cur_ = QVector2D(event->pos());
            update();
        }
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
        if (move_) {
            double scale = (rt_ - lb_).x() / width_;
            pressed_ *= scale;
            cur_ *= scale;

            pressed_ += lb_;
            cur_ += lb_;


            lb_ = QVector2D(std::min(cur_.x(), pressed_.x()), std::min(cur_.y(), pressed_.y()));
            long double width = std::max(cur_.x(), pressed_.x()) - lb_.x();
            rt_ = lb_ + QVector2D(width, width * (height_ * 1.0 / width_ ));

            update();
        }
        move_ = false;
    }

private:
    int width_, height_;
    QVector2D lb_, rt_;
    QVector2D pressed_;
    QVector2D cur_;
    QPixmap pixmap_;
    bool move_ = false;

    void gen_pixmap();
};

#endif // CANVAS_H
