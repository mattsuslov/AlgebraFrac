#include "canvas.h"
Canvas::Canvas()
{
    width_ = 1000, height_ = 700;
    rt_ = {2, 2};
    lb_ = {-2, -1};
    update();
}

int mondelbrot(Complex c, int n) {
    Complex z(0);
    for (int i = 0; i < n; ++i) {
        if (z.toVector().length() > 2) return i;
        z = z * z + c;
    }
    return -1;
}

int zhulia(Complex z, int n) {
    Complex c = Complex(-0.74543, 0.11301);
    for (int i = 0; i < n; ++i) {
        if (z.toVector().length() > 2) return i;
        z = z * z + c;
    }
    return -1;
}

int nuton(Complex z, int n) {
    for (int i = 0; i < n; ++i) {
        if (z.toVector().length() > 10) return i;
        z = z - (z * z * z * z * z - 1) / (4 * z * z * z * z);
    }
    return -1;
}

void Canvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    if (!move_) {
        gen_pixmap();
    }
    painter->drawPixmap(0, 0, width_, height_, pixmap_);
    if (move_) {
        double width = std::max(cur_.x(), pressed_.x()) - std::min(cur_.x(), pressed_.x());
        painter->setBrush(QColor(200, 200, 200, 100));
        painter->drawRect(std::min(cur_.x(), pressed_.x()), std::min(cur_.y(), pressed_.y()), width, width * (height_ * 1.0 / width_));
    }
}

void Canvas::gen_pixmap() {
    QPixmap pixmap(width_, height_);
    QPainter painter(&pixmap);
    double scale = width_ / (rt_ - lb_).x();
    for (double y = lb_.y(), dy = 1.0 / scale; y <= rt_.y(); y += dy) {
        for (double x = lb_.x(), dx = 1.0 / scale; x <= rt_.x(); x += dx) {
            Complex c(x, y);
            int MAX_N = 100;
            int n = nuton(c, MAX_N);
//            int n = zhulia(c, MAX_N);
//            int n = mondelbrot(c, MAX_N);
            painter.setPen(QColor(Qt::black));
            if (n == -1) {
                painter.setPen(QColor(Qt::black));
            } else {
                double k = pow(n * 1.0 / MAX_N, 0.3);
                painter.setPen(QColor(k * 256, 0, k * 256));
            }
            painter.drawPoint((x - lb_.x()) * scale, (y - lb_.y()) * scale);
        }
    }
    pixmap_ = pixmap;
}
