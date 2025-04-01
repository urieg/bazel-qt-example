#include "plane.h"

#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QWidget>
#include <QKeyEvent>


Plane::Plane(QWidget *parent) : QWidget(parent) {
    cursor_pos_ = QPoint(-1, -1);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

}

Plane::~Plane() {
}

void Plane::mousePressEvent(QMouseEvent *event) {
    if (mode_ == Mode::Polygons) {
        if (event->button() == Qt::LeftButton) {
            if (drawing_ == false) {
                drawing_ = true;
                controller_.AddPolygon(Polygon());
            }
            controller_.AddVertexToLastPolygon(event->pos());
        } else {
            drawing_ = false;
        }
    }
    update();
}

void Plane::mouseMoveEvent(QMouseEvent *event) {
    if (mode_ == Mode::Light) {
        cursor_pos_ = event->pos();
        cursor_visible_ = true;
        update();
    }
}

void Plane::leaveEvent(QEvent *event) {
    if (mode_ == Mode::Light) {
        cursor_pos_ = QPoint(-1,-1);
        cursor_visible_ = false;
        update();
    }
}

void Plane::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    //painter.fillRect(rect(), Qt::white);
    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(QColor(0, 0, 0, 100));

    QPoint prev_vertex;
    for (const auto& polygon : controller_.GetPolygons()) {
        for (int i = 0; i < polygon.GetVerticesNumber(); i++) {
            auto vertex = polygon.GetVertex(i);
            painter.drawEllipse(vertex, 5, 5);
            if (i) {
                painter.drawLine(prev_vertex, vertex);
            }
            prev_vertex = vertex;
        }
    }

    if (cursor_visible_) {
        painter.setPen(QPen(Qt::red, 2));
        painter.setBrush(QColor(255, 0, 0, 100));
        painter.drawEllipse(cursor_pos_, 5, 5);
    }
}

void Plane::keyPressEvent(QKeyEvent *event) {

    switch(event->key()) {
        case Qt::Key_L:
            if (mode_ != Mode::Light) {
                mode_ = Mode::Light;
                drawing_ = false;
                cursor_visible_ = true;
                update();
            }
            break;
        case Qt::Key_P:
            if (mode_ != Mode::Polygons) {
                mode_ = Mode::Polygons;
                cursor_visible_ = false;
                update();
            }
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}
